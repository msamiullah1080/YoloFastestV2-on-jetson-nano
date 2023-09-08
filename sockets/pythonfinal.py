import numpy as np
import socket
import struct
import supervision as sv

IP = "127.0.0.1"
PORT = 5010
ADDR = (IP, PORT)
SIZE = 4096  # Size of integer in bytes



# Define the structure of TargetBox in Python
class TargetBox:
    def __init__(self, x1, y1, x2, y2, cate, score):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.cate = cate
        self.score = score

# Class names
class_names = [
    "background", "person", "bicycle",
    "car", "motorbike", "aeroplane", "bus", "train", "truck",
    "boat", "traffic light", "fire hydrant", "stop sign",
    "parking meter", "bench", "bird", "cat", "dog", "horse",
    "sheep", "cow", "elephant", "bear", "zebra", "giraffe",
    "backpack", "umbrella", "handbag", "tie", "suitcase",
    "frisbee", "skis", "snowboard", "sports ball", "kite",
    "baseball bat", "baseball glove", "skateboard", "surfboard",
    "tennis racket", "bottle", "wine glass", "cup", "fork",
    "knife", "spoon", "bowl", "banana", "apple", "sandwich",
    "orange", "broccoli", "carrot", "hot dog", "pizza", "donut",
    "cake", "chair", "sofa", "pottedplant", "bed", "diningtable",
    "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard",
    "cell phone", "microwave", "oven", "toaster", "sink",
    "refrigerator", "book", "clock", "vase", "scissors",
    "teddy bear", "hair drier", "toothbrush"
]


def main():
 
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(ADDR)

    # Receive the data
    data = b""
    while True:
        packet = client_socket.recv(4096)
        if not packet:
            break
        data = packet

        # Unpack the received data into TargetBox instances
        boxes_data_size = len(data)
        num_boxes = boxes_data_size // struct.calcsize("iiiiif")
        boxes_format = "iiiiif" * num_boxes
        unpacked_data = struct.unpack(boxes_format, data)
    
        # Create a list of TargetBox instances
        target_boxes = []
        for i in range(0, num_boxes * 6, 6):
            target_boxes.append(TargetBox(*unpacked_data[i:i+6]))

        # Create numpy arrays for xyxy, confidence, and class_id
        xyxy = np.zeros((num_boxes, 4))
        confidence = np.zeros(num_boxes)
        class_id = np.zeros(num_boxes, dtype=int)

        # Fill the numpy arrays with data from target_boxes
        for i, box in enumerate(target_boxes):
            xyxy[i] = [box.x1, box.y1, box.x2, box.y2]
            confidence[i] = round(box.score * 100, 2)
            class_id[i] = box.cate + 1

        #if num_boxes == 0:
         #   print("No detections in this frame.")
        #else:


        # Create a Detections object
        detections = sv.Detections(xyxy=xyxy, confidence=confidence, class_id=class_id)

        # Print the received data
        for xyxy, mask, confidence, class_id, tracker_id in detections:
            print(f"xyxy: {xyxy}")
            print(f"Confidence: {confidence}")
            print(f"Class ID : {class_id}")



        current_frame_detection_count = len(target_boxes)
        print(f"Number of detections in this frame: {current_frame_detection_count}")

        client_socket.send("kuch bhi".encode())

    # Close the connection
    client_socket.close()
    print("[DISCONNECTED] Connection closed")

if __name__ == "__main__":
    main()
