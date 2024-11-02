import time
import random
import json
from kafka import KafkaProducer
from kafka.errors import KafkaError


producer = KafkaProducer(
    bootstrap_servers=['localhost:9092'],
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
    # security_protocol="SASL_PLAINTEXT",
    # sasl_mechanism="PLAIN",
    # sasl_plain_username="admin",
    # sasl_plain_password="admin",
)

// TODO: implement real call to RIOT API 
def generate_game_data():
    return {
        "t1_towerKills": random.randint(0, 11),
        "t1_inhibitorKills": random.randint(0, 3),
        "t1_baronKills": random.randint(0, 2),
        "t1_dragonKills": random.randint(0, 4),
        "t1_riftHeraldKills": random.randint(0, 2),
        "t2_towerKills": random.randint(0, 11),
        "t2_inhibitorKills": random.randint(0, 3),
        "t2_baronKills": random.randint(0, 2),
        "t2_dragonKills": random.randint(0, 4),
        "t2_riftHeraldKills": random.randint(0, 2)
    }


# Main loop to continuously send mock data
try:
    while True:
        game_data = generate_game_data()
        future = producer.send('lol-game-data', value=game_data)
        record_metadata = future.get(timeout=10)
        print(f"Sent: {game_data} to {record_metadata.topic} partition {record_metadata.partition}")
        time.sleep(5)

except KafkaError as e:
    print(f"Error sending message: {e}")
finally:
    producer.close()
