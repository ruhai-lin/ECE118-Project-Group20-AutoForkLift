import sensor
import time
import math
from pyb import UART

# --------------------- 相机初始化 ---------------------
sensor.reset()
# sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_pixformat(sensor.RGB565)

sensor.set_framesize(sensor.QVGA)
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
alpha = 0.7
lost_counter = 0
max_lost = 5

def degrees(radians):
    return (180 * radians) / math.pi

# --------------------- 主循环 ---------------------
while True:
    clock.tick()
    img = sensor.snapshot()

    img.lens_corr(1.6)
    img.histeq()

    tag_found = False

    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y, pose_only=False):
        tag_found = True
        lost_counter = 0

        tag_id = tag.id
        Tx, Ty, Tz = tag.x_translation * 10, tag.y_translation * 10, tag.z_translation * 10

        # 一阶滤波
        Tx = alpha * last_Tx + (1 - alpha) * Tx
        Ty = alpha * last_Ty + (1 - alpha) * Ty
        Tz = alpha * last_Tz + (1 - alpha) * Tz

        last_Tx, last_Ty, last_Tz = Tx, Ty, Tz

        Rx = degrees(tag.x_rotation)
        Ry = degrees(tag.y_rotation)
        Rz = degrees(tag.z_rotation)

        longitudinal_distance = Tz * math.cos(tag.y_rotation)
        lateral_distance = Tz * math.sin(tag.y_rotation)


        # 绘制矩形和十字标记
        img.draw_rectangle(tag.rect, color=(255, 0, 0))
        img.draw_cross(tag.cx, tag.cy, color=(0, 255, 0))

        # 绘制信息文字
        text = "ID:%d T:(%.1f,%.1f,%.1f) \n R:(%d,%d,%d)\nLD:%.1f \n LtD:%.1f" % (
            tag.id,
            tag.x_translation, tag.y_translation, tag.z_translation,
            int(degrees(tag.x_rotation)),
            int(degrees(tag.y_rotation)),
            int(degrees(tag.z_rotation)),
            longitudinal_distance,
            lateral_distance
        )
        img.draw_string(tag.cx, tag.cy - 30, text, mono_space=False)

        # 串口发送格式
        msg = "%d,%d,%d,%d,%d,%d,%d\r\n" % (
            tag_id, int(Tx), int(Ty), int(Tz), int(Rx), int(Ry), int(Rz)
        )
        uart.write(msg)
        break

    if not tag_found:
        lost_counter += 1
        if lost_counter >= max_lost:
            uart.write("-1,0,0,0,0,0,0\r\n")
            lost_counter = max_lost