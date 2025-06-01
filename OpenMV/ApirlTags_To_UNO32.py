import sensor
import time
import math
import pyb
from pyb import UART

# --------------------- 相机初始化 ---------------------
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
# sensor.set_pixformat(sensor.RGB565)

sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

# 镜头内参（适用于OV7725 + 2.8mm镜头）
f_x = (2.8 / 3.984) * 320
f_y = (2.8 / 2.952) * 240
c_x = 320 * 0.5
c_y = 240 * 0.5

# --------------------- 串口初始化 ---------------------
uart = UART(3, 115200, timeout_char=200)

# --------------------- 状态初始化 ---------------------
last_Tx, last_Ty, last_Tz = 0, 0, 0
last_Rx, last_Ry, last_Rz = 0, 0, 0
alpha = 0.7
lost_counter = 0
max_lost = 5

def degrees(radians):
    return (180 * radians) / math.pi

# --------------------- 主循环 ---------------------
# 初始状态
last_sent_id = -2  # -2 表示从未发送过；-1 表示未检测到tag；0~4表示上一个发送的tag

while True:
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(1.6)
    img.histeq()

    tag_found = False

    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y, pose_only=False):
        tag_found = True
        lost_counter = 0
        pyb.LED(3).off()

        tag_id = tag.id
        Tx, Ty, Tz = tag.x_translation * 10, tag.y_translation * 10, tag.z_translation * 10
        Rx, Ry, Rz = degrees(tag.x_rotation), degrees(tag.y_rotation), degrees(tag.z_rotation)

        # 一阶滤波
        Tx = alpha * last_Tx + (1 - alpha) * Tx
        Ty = alpha * last_Ty + (1 - alpha) * Ty
        Tz = alpha * last_Tz + (1 - alpha) * Tz
        Rx = alpha * last_Rx + (1 - alpha) * Rx
        Ry = alpha * last_Ry + (1 - alpha) * Ry
        Rz = alpha * last_Rz + (1 - alpha) * Rz

        last_Tx, last_Ty, last_Tz = Tx, Ty, Tz
        last_Rx, last_Ry, last_Rz = Rx, Ry, Rz

        # 图像显示（可选）
        img.draw_rectangle(tag.rect, color=(255, 0, 0))
        img.draw_cross(tag.cx, tag.cy, color=(0, 255, 0))

        text = "ID:%d T:(%.1f,%.1f,%.1f) \n R:(%d,%d,%d)" % (
            tag.id,
            tag.x_translation, tag.y_translation, tag.z_translation,
            int(degrees(tag.x_rotation)),
            int(degrees(tag.y_rotation)),
            int(degrees(tag.z_rotation))
        )
        img.draw_string(tag.cx, tag.cy - 30, text, mono_space=False)

        # ✅ 只有在 tag ID 发生变化时才发送
        if tag_id != last_sent_id:
            msg = "%d,%d,%d,%d,%d,%d,%d\r\n" % (
                tag_id, int(Tx), int(Ty), int(Tz), int(Rx), int(Ry), int(Rz)
            )
            uart.write(msg)
            last_sent_id = tag_id
        break

    # 如果没有检测到 tag，且上一次发送的不是 -1，则发送一次丢失信号
    if not tag_found:
        lost_counter += 1
        if lost_counter >= max_lost:
            pyb.LED(3).on()
            if last_sent_id != -1:
                uart.write("-1,0,0,0,0,0,0\r\n")
                last_sent_id = -1
            lost_counter = max_lost
