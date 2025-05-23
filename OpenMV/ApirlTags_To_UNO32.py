# april_tag_uart_send.py

import sensor
import time
import math
from pyb import UART

# 相机初始化
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

# 摄像头内参（适用于OV7725 + 2.8mm镜头）
f_x = (2.8 / 3.984) * 160
f_y = (2.8 / 2.952) * 120
c_x = 160 * 0.5
c_y = 120 * 0.5

# 初始化 UART3
uart = UART(3, 115200, timeout_char=200)

def degrees(radians):
    return (180 * radians) / math.pi

while True:
    clock.tick()
    img = sensor.snapshot()
    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y):
        img.draw_rectangle(tag.rect, color=(255, 0, 0))
        img.draw_cross(tag.cx, tag.cy, color=(0, 255, 0))

        tag_id = tag.id
        Tx, Ty, Tz = tag.x_translation, tag.y_translation, tag.z_translation
        Rx, Ry, Rz = degrees(tag.x_rotation), degrees(tag.y_rotation), degrees(tag.z_rotation)

        # 串口发送格式：包含Tag ID
        msg = "Tag: %d, Tx: %d, Ty: %d, Tz: %d, Rx: %d, Ry: %d, Rz: %d\r\n" % (tag_id, Tx*10, Ty*10, Tz*10, Rx, Ry, Rz)
        uart.write(msg)
        # print(msg)

    # print("FPS:", clock.fps())
