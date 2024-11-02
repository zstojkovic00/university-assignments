from pyspark.sql import SparkSession
from pyspark.sql.functions import from_json, col
from pyspark.sql.types import StructType, StructField, IntegerType
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.classification import LogisticRegressionModel

# Initialize SparkSession with Kafka integration
spark = SparkSession.builder \
    .appName("LOL Game Predictor") \
    .config("spark.jars.packages", "org.apache.spark:spark-sql-kafka-0-10_2.12:3.1.2") \
    .getOrCreate()

# .config("spark.kafka.sasl.mechanism", "PLAIN") \
# .config("spark.kafka.security.protocol", "SASL_PLAINTEXT") \
# .config("spark.kafka.sasl.jaas.config",
#         "org.apache.kafka.common.security.plain.PlainLoginModule required username='admin'  password='admin';") \

spark.sparkContext.setLogLevel("WARN")

# Define schema for incoming data
schema = StructType([
    StructField("t1_towerKills", IntegerType(), True),
    StructField("t1_inhibitorKills", IntegerType(), True),
    StructField("t1_baronKills", IntegerType(), True),
    StructField("t1_dragonKills", IntegerType(), True),
    StructField("t1_riftHeraldKills", IntegerType(), True),
    StructField("t2_towerKills", IntegerType(), True),
    StructField("t2_inhibitorKills", IntegerType(), True),
    StructField("t2_baronKills", IntegerType(), True),
    StructField("t2_dragonKills", IntegerType(), True),
    StructField("t2_riftHeraldKills", IntegerType(), True)
])

# Load pretrained model
model = LogisticRegressionModel.load("logistic_regression_model")


# function that process each batch of data
def predict(df):
    if not df.isEmpty():
        print(f"Received {df.count()} records")
        assembler = VectorAssembler(inputCols=df.columns, outputCol="features")
        df_assembled = assembler.transform(df)

        predictions = model.transform(df_assembled)

        print("Predictions:")
        predictions.select("features", "prediction").show(truncate=False)
    else:
        print("Received empty batch")


# Subscribe to kafka topic lol-game-data
df = spark \
    .readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "localhost:9092") \
    .option("subscribe", "lol-game-data") \
    .load()

# Parse json data from Kafka
parsed_df = df.select(from_json(col("value").cast("string"), schema).alias("data")).select("data.*")

# Start streaming query and process requests
query = parsed_df \
    .writeStream \
    .foreachBatch(predict) \
    .start()

query.awaitTermination()
