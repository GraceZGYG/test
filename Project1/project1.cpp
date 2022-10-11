#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
const int N = 1e5 + 5;
double dT = 0.993;
double T = 2000;
const double eps = 1e-14;
struct vega {
    double x, y;
}e[N];
int n;
//输入我们随机生成的点A 坐标 x0, y0
double func(double x, double y) {
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        double xx = e[i].x, yy = e[i].y; // xx 就是 xi ，yy 就是 yi
        double p = fabs(e[i].x - x); // x0 - xi
        double q = fabs(e[i].y - y); // y0 - yi
        ans += (sqrt((p * p + q * q))); // ans加上到随机点A到点i的距离
    }
    return ans;
}
void SA() {
    //随机生成点A(x0,y0)，这里我直接赋值为了0。当然也可以写rand()，差别都不大。
    double x = 0, y = 0;
    //生成的点A(x0,y0)对应的函数值f(x0, y0)
    double f = func(x, y);
    while (T > eps) {
        //这里对x和y同时进行一个偏移，很明显在一个平面中，上下左右都可以移动，所以我们选择了rand() * 2 - RAND_MAX
        //对于每个点，我们的偏移幅度都要 * T,温度越高，偏移量越大
        double dx = x + (rand() * 2 - RAND_MAX) * T;
        double dy = y + (rand() * 2 - RAND_MAX) * T;
        //算出偏移后的点B(dx, dy)对应的函数值f(dx, dy)
        double df = func(dx, dy);
        //这里就是关键的地方了，很明显我们需要算出来的function值越小，就更加优秀
        //所以如果新来的值df 比 f更小，我们百分百接受
        if (df < f) {
            //注意更新所有变量
            f = df; y = dy; x = dx;
        }
        //否则我们概率接受，这里的需要写 f - df了，因为这样才是负值
        else if (exp((f - df) / T) * RAND_MAX > rand()) {
            //注意更新所有变量
            f = df; y = dy; x = dx;
        }
        //降低温度
        T = T * dT;
    }
    //输出答案
    printf("%.f\n", f);
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &e[i].x, &e[i].y);
    }
    SA();
}
