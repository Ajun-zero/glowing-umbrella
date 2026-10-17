import tkinter as tk
import random
import math

# 5 句固定爱意词语
LOVE_WORDS = [
    "我爱你",
    "我喜欢你",
    "亲爱的",
    "i love you",
    "永远爱你",
]

# 五颜六色的颜色池（粉/橙/黄/绿/蓝/紫/玫红）
COLORS = [
    "#FF4D6D", "#FF6B9D", "#FF8FA3", "#FFA5C3",
    "#FF8C42", "#FFA62B", "#FFB74D", "#FFD54F",
    "#A8E063", "#7ED957", "#4CAF50", "#00C9A7",
    "#4D96FF", "#64B5F6", "#5B8FF9", "#42A5F5",
    "#845EC2", "#9575CD", "#BA68C8", "#D65DB1",
    "#E056FD", "#FF6EC7", "#F3904F", "#FF9A76",
]

WIN_W = 130       # 弹窗宽
WIN_H = 90        # 弹窗高
N_POINTS = 50     # 弹窗数量


def heart_points_by_arclength(n):
    """
    用爱心参数方程采样，再按弧长均匀取 n 个点，
    保证点沿爱心轮廓分布均匀，爱心才不会一边挤一边空。
    """
    samples = 2000
    pts = []
    for i in range(samples):
        t = 2 * math.pi * i / samples
        x = 16 * math.sin(t) ** 3
        y = (13 * math.cos(t) - 5 * math.cos(2 * t)
             - 2 * math.cos(3 * t) - math.cos(4 * t))
        pts.append((x, y))

    # 累计弧长
    lens = [0.0]
    for i in range(1, len(pts)):
        dx = pts[i][0] - pts[i - 1][0]
        dy = pts[i][1] - pts[i - 1][1]
        lens.append(lens[-1] + math.hypot(dx, dy))
    total = lens[-1]

    # 等弧长取点
    result = []
    for k in range(n):
        target = total * k / n
        lo, hi = 0, len(lens) - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if lens[mid] < target:
                lo = mid + 1
            else:
                hi = mid
        result.append(pts[lo])
    return result


def create_msgbox(root, x, y, text, color, on_close):
    """创建一个模拟 Windows 提示框的彩色弹窗，中心定位在 (x, y)"""
    win = tk.Toplevel(root)
    win.withdraw()                    # 先隐藏，避免闪烁
    win.overrideredirect(True)        # 去掉系统边框
    win.attributes("-topmost", True)  # 置顶

    px = int(x - WIN_W / 2)
    py = int(y - WIN_H / 2)
    win.geometry(f"{WIN_W}x{WIN_H}+{px}+{py}")

    # 外框（深色 1px 描边）
    outer = tk.Frame(win, bg="#333333")
    outer.pack(fill="both", expand=True)

    # ---- 标题栏（彩色）----
    titlebar = tk.Frame(outer, bg=color, height=22)
    titlebar.pack(fill="x")
    titlebar.pack_propagate(False)

    tk.Label(titlebar, text="  爱意提示", bg=color, fg="white",
             font=("Microsoft YaHei", 8, "bold"), anchor="w"
             ).pack(side="left", fill="y")

    close_lbl = tk.Label(titlebar, text="✕", bg=color, fg="white",
                         font=("Arial", 8, "bold"), width=3, cursor="hand2")
    close_lbl.pack(side="right", fill="y")
    close_lbl.bind("<Button-1>", lambda e: on_close(win))

    # ---- 内容区（白色背景）----
    content = tk.Frame(outer, bg="white")
    content.pack(fill="both", expand=True, padx=1, pady=(0, 1))

    row = tk.Frame(content, bg="white")
    row.pack(expand=True, pady=(4, 0))

    tk.Label(row, text="❤", bg="white", fg=color,
             font=("Segoe UI Symbol", 13)).pack(side="left", padx=(0, 4))
    tk.Label(row, text=text, bg="white", fg=color,
             font=("Microsoft YaHei", 11, "bold")).pack(side="left")

    ok_btn = tk.Label(content, text=" 确 定 ", bg=color, fg="white",
                      font=("Microsoft YaHei", 8, "bold"),
                      padx=6, pady=1, cursor="hand2")
    ok_btn.pack(pady=(2, 6))
    ok_btn.bind("<Button-1>", lambda e: on_close(win))

    win.deiconify()                   # 显示出来
    return win


def main():
    root = tk.Tk()
    root.withdraw()

    sw = root.winfo_screenwidth()
    sh = root.winfo_screenheight()

    # 1) 取爱心轮廓点
    pts = heart_points_by_arclength(N_POINTS)
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    xmin, xmax = min(xs), max(xs)
    ymin, ymax = min(ys), max(ys)
    w_raw = xmax - xmin
    h_raw = ymax - ymin

    # 2) 缩放到屏幕：爱心占宽 62%、高 72%，居中
    target_w = sw * 0.62
    target_h = sh * 0.72
    scale = min(target_w / w_raw, target_h / h_raw)

    cx, cy = sw / 2, sh / 2

    def to_screen(x, y):
        px = cx + (x - (xmin + xmax) / 2) * scale
        py = cy - (y - (ymin + ymax) / 2) * scale   # y 轴翻转
        return px, py

    screen_pts = [to_screen(x, y) for (x, y) in pts]

    # 3) 打乱颜色，保证五颜六色
    colors = COLORS[:]
    while len(colors) < N_POINTS:
        colors += COLORS
    random.shuffle(colors)
    colors = colors[:N_POINTS]

    windows = []
    remaining = [0]

    def on_close(win):
        try:
            win.destroy()
        except tk.TclError:
            pass
        remaining[0] -= 1
        # 所有窗口都已弹出且全部关闭后退出
        if remaining[0] <= 0 and len(windows) >= N_POINTS:
            root.after(150, root.quit)

    # 4) 逐个弹出，形成爱心生长动画
    def pop_next(i=0):
        if i >= N_POINTS:
            return
        x, y = screen_pts[i]
        jx = random.uniform(-3, 3)   # 微小抖动，更自然
        jy = random.uniform(-3, 3)
        text = LOVE_WORDS[i % len(LOVE_WORDS)]
        color = colors[i]
        w = create_msgbox(root, x + jx, y + jy, text, color, on_close)
        windows.append(w)
        remaining[0] += 1
        root.after(30, lambda: pop_next(i + 1))

    pop_next()
    root.mainloop()


if __name__ == "__main__":
    main()
