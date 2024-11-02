import os
import cv2
import numpy as np
import base64
from flask import Flask
from flask_socketio import SocketIO, emit
from flask_cors import CORS
from cvzone.HandTrackingModule import HandDetector
import time

app = Flask(__name__)
CORS(app)
socketio = SocketIO(app, cors_allowed_origins="*")

detector = HandDetector(staticMode=True, maxHands=1, modelComplexity=1, detectionCon=0.8, minTrackCon=0.5)


last_thumb_time = 0
thumb_interval = 1


def is_thumb_up(landmarks):
    thumb_tip_y = landmarks[4][1]  # THUMB_TIP
    thumb_mcp_y = landmarks[2][1]  # THUMB_MCP
    index_mcp_y = landmarks[5][1]  # INDEX_FINGER_MCP
    return thumb_tip_y < thumb_mcp_y < index_mcp_y


@socketio.on('process_frame')
def handle_frame(data):
    global last_thumb_time

    # Decode the base64 image
    image_data = data['image']
    nparr = np.frombuffer(base64.b64decode(image_data.split(',')[1]), np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

    if not os.path.exists('received_images'):
        os.makedirs('received_images')
    cv2.imwrite('received_images/received_frame.jpg', img)

    # Process the image to detect hands
    hands, img = detector.findHands(img, flipType=True)

    answer = None
    if hands:
        hand = hands[0]

        landmarks = hand["lmList"]

        current_time = time.time()
        if is_thumb_up(landmarks):
            if current_time - last_thumb_time > thumb_interval:
                print("Thumb is up!")
                emit('thumb_up', {'status': 'Thumb is up!'})
                last_thumb_time = current_time
            return

        fingers = detector.fingersUp(hand)
        print('Fingers up:', fingers)
        num_fingers = fingers.count(1)
        if 1 <= num_fingers <= 4:
            answer = num_fingers - 1
        print('Answer:', answer)
        emit('answer', {'answer': answer})
    else:
        print('Fingers up: 0')

if __name__ == '__main__':
    socketio.run(app, debug=True)
