using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        PointF[] BezierToPoints(PointF[] bs, int numSegments)
        {
            var len = (bs.Length - 1) / 3;
            var rtv = new PointF[numSegments * len];
            var step = 1.0f / numSegments;
            for (int i = 0; i < numSegments; ++i)
            {
                var t = step * i;
                var t1 = 1 - t;
                for (int j = 0; j < len; ++j)
                {
                    var idx = j * 3;
                    rtv[j * numSegments + i] = new PointF(
                        t1 * t1 * t1 * bs[idx].X + 3 * t * t1 * t1 * bs[idx + 1].X + 3 * t * t * (1 - t) * bs[idx + 2].X + t * t * t * bs[idx + 3].X,
                        t1 * t1 * t1 * bs[idx].Y + 3 * t * t1 * t1 * bs[idx + 1].Y + 3 * t * t * (1 - t) * bs[idx + 2].Y + t * t * t * bs[idx + 3].Y);
                }
            }
            return rtv;
        }

        PointF[] CurveToBezier(PointF[] cs, float tension = 0.3f)
        {
            var n = cs.Length;
            var len = n * 3 - 2;
            var bs = new PointF[len];

            bs[0] = cs[0];
            bs[1].X = tension * (cs[1].X - cs[0].X) + cs[0].X;
            bs[1].Y = tension * (cs[1].Y - cs[0].Y) + cs[0].Y;

            for (int i = 0; i < n - 2; i++)
            {
                var xDiff = (cs[i + 2].X - cs[i].X) * tension;
                var yDiff = (cs[i + 2].Y - cs[i].Y) * tension;

                bs[3 * i + 2].X = cs[i + 1].X - xDiff;
                bs[3 * i + 2].Y = cs[i + 1].Y - yDiff;
                bs[3 * i + 3] = cs[i + 1];
                bs[3 * i + 4].X = cs[i + 1].X + xDiff;
                bs[3 * i + 4].Y = cs[i + 1].Y + yDiff;
            }

            bs[len - 2].X = tension * (cs[n - 2].X - cs[n - 1].X) + cs[n - 1].X;
            bs[len - 2].Y = tension * (cs[n - 2].Y - cs[n - 1].Y) + cs[n - 1].Y;
            bs[len - 1] = cs[n - 1];

            return bs;
        }

        PointF[] CurveToPoints(PointF[] cs, float tension = 0.3f, int n = 50, int cutHead = 0, int cutTail = 0)
        {
            // 插值为 Bezier (2控制点)
            var bs = CurveToBezier(cs, tension);

            // 切掉不要的部分
            var cutLen = cutHead + cutTail;
            if (cutLen > 0)
            {
                var newLen = (cs.Length - cutLen) * 3 + 1;
                var tmp = new PointF[newLen];
                Array.Copy(bs, cutHead * 3, tmp, 0, newLen);
                bs = tmp;
            }

            // 转为点集合
            return BezierToPoints(bs, n);
        }


        private void DrawCurve(PaintEventArgs e, PointF[] ps, float tension = 0.3f, int n = 50, int cutHead = 0, int cutTail = 0)
        {
            var points = CurveToPoints(ps, tension, n, cutHead, cutTail);

            // 0,0 点在窗口中的位置
            var _0_0 = new PointF(300, 300);

            var redPen = new Pen(Color.Red, 3);
            for (int i = points.Length - 1; i >= 0; --i)
            {
                var o = points[i];

                // 上下翻转并将 0,0 移动到屏幕中间 for 修正 winform 下的显示. opengl 不需要
                o.X += _0_0.X;
                o.Y = -o.Y + _0_0.Y;

                e.Graphics.DrawEllipse(redPen, new RectangleF(o, new SizeF(2, 2)));
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // 途径点( 屏幕中心 0,0 的 opengl 坐标系 )
            var ps = new PointF[] {
                new PointF(-100, 0),
                new PointF(-100, 100),
                new PointF(0, 0),
                new PointF(100, 100),
                new PointF(0, 100),
                new PointF(-100, -100),
            };

            //DrawCurve(e, ps);

            ps = new PointF[] {
                //new PointF(0, 100),
                new PointF(150, 0),
                new PointF(0, -100),
                new PointF(-150, 0),

                new PointF(0, 100),
                new PointF(150, 0),
                new PointF(0, -100),
                new PointF(-150, 0),

                new PointF(0, 100),
                new PointF(150, 0),
                new PointF(0, -100),
                //new PointF(-150, 0),
            };

            DrawCurve(e, ps, 0.5f, 50, 3, 3);
        }

    }
}
