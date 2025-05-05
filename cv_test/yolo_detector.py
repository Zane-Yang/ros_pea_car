#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import torch
from std_msgs.msg import String

class YOLODetector:
    def __init__(self):
        try:
            self.bridge = CvBridge()
            self.model = torch.hub.load('ultralytics/yolov5', 'yolov5s')  # 加载 YOLOv5
            self.image_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.callback)
            self.detection_pub = rospy.Publisher("/detections", String, queue_size=10)
        except Exception as e:
            rospy.logerr(f"初始化出错: {e}")

    def callback(self, msg):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            results = self.model(cv_img)  # YOLO 检测
            detections = results.pandas().xyxy[0]  # 获取检测结果
            for _, row in detections.iterrows():
                if row["name"] in ["person", "cat", "dog"]:  # 只检测人和动物
                    self.detection_pub.publish(f"{row['name']} detected")
        except Exception as e:
            rospy.logerr(f"回调函数出错: {e}")

if __name__ == '__main__':
    try:
        rospy.init_node('yolo_detector', anonymous=True)
        detector = YOLODetector()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass