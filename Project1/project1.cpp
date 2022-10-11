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
//��������������ɵĵ�A ���� x0, y0
double func(double x, double y) {
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        double xx = e[i].x, yy = e[i].y; // xx ���� xi ��yy ���� yi
        double p = fabs(e[i].x - x); // x0 - xi
        double q = fabs(e[i].y - y); // y0 - yi
        ans += (sqrt((p * p + q * q))); // ans���ϵ������A����i�ľ���
    }
    return ans;
}
void SA() {
    //������ɵ�A(x0,y0)��������ֱ�Ӹ�ֵΪ��0����ȻҲ����дrand()����𶼲���
    double x = 0, y = 0;
    //���ɵĵ�A(x0,y0)��Ӧ�ĺ���ֵf(x0, y0)
    double f = func(x, y);
    while (T > eps) {
        //�����x��yͬʱ����һ��ƫ�ƣ���������һ��ƽ���У��������Ҷ������ƶ�����������ѡ����rand() * 2 - RAND_MAX
        //����ÿ���㣬���ǵ�ƫ�Ʒ��ȶ�Ҫ * T,�¶�Խ�ߣ�ƫ����Խ��
        double dx = x + (rand() * 2 - RAND_MAX) * T;
        double dy = y + (rand() * 2 - RAND_MAX) * T;
        //���ƫ�ƺ�ĵ�B(dx, dy)��Ӧ�ĺ���ֵf(dx, dy)
        double df = func(dx, dy);
        //������ǹؼ��ĵط��ˣ�������������Ҫ�������functionֵԽС���͸�������
        //�������������ֵdf �� f��С�����ǰٷְٽ���
        if (df < f) {
            //ע��������б���
            f = df; y = dy; x = dx;
        }
        //�������Ǹ��ʽ��ܣ��������Ҫд f - df�ˣ���Ϊ�������Ǹ�ֵ
        else if (exp((f - df) / T) * RAND_MAX > rand()) {
            //ע��������б���
            f = df; y = dy; x = dx;
        }
        //�����¶�
        T = T * dT;
    }
    //�����
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
