//Simulated Annealing
#include <bits/stdc++.h>
using namespace std;
//n代表我们最后函数要逼近的值
double n;
//x表示我们随机产生的那个数的平方和n的靠近程度
double func(double x) {
    return fabs(x * x - n);
}
double T = 20000; //初始温度，初始温度主要是看题目开始需要跳转的幅度。
double dT = 0.993; //变化率，这里需要速度稍微慢一点，写0.995 或者 0.997都可以，但是越靠近1速度就越慢 
const double eps = 1e-14; //10的-14次方已经非常小了，写这个大概率没问题
void SA() {
    //首先随机生成一个点x0，这里我用0代替。
    double x = 0;
    //算出x平方和n的差距f(x0)
    double f = func(x);
    while (T > eps) {
        //这里x0既可以变小，也可以变大，所以我们正负都要进行一个跳转,算出变换后的点dx
        double dx = x + (2 * rand() - RAND_MAX) * T;
        //但是请注意，dx很明显要保证 >= 0才行，因为算术平方根的定义域是>=0，因此小于0就重新随机
        while (dx < 0) dx = x + (2 * rand() - RAND_MAX) * T;
        //算出变换后的点dx的平方和n的差距，f(dx)
        double df = func(dx);
        //这里就是关键的地方了，很明显我们需要算出来的function值越小，自变量x更加接近那个根号值。
        //所以如果新来的值df 比 f更小，我们百分百接受
        if (df < f) {
            //注意更新所有变量
            f = df; x = dx;
        }
        //否则我们概率接受，这里的需要写 f - df了，因为这样才是负值。负值说明我们并不是贪心接受的，他是不太好的值。
        else if (exp((f - df) / T) * RAND_MAX > rand()) {
            //注意更新所有变量
            f = df; x = dx;
        }
        //温度下降一下
        T *= dT;
    }
    printf("%.8lf", x);
}
int main()
{
    cin >> n;
    SA();
}
