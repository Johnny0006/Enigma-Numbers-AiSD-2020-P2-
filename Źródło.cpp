#include <iostream>
#include <stdio.h>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS

struct Wirnik {
    int* number;
    int* number_reverse;
    int notch_amount;
    int* notch;
};



void crypting(Wirnik* w, int* reflektor, int* spin, int w_amount, int n);
int calculating_out(int out, int delta, int spin, bool minus_spin, int n);
bool spinning(int* spin, bool double_step, Wirnik* w, int w_amount, int n);



int main()
{
    int n, m, sign, amount, l;

    scanf_s("%i", &n);
    scanf_s("%i", &m);

    Wirnik* w = new Wirnik[m];

    for (int i = 0; i < m; i++) {

        w[i].number = new int[n];
        w[i].number_reverse = new int[n];

        for (int j = 0; j < n; j++) {

            scanf_s("%i", &sign);

            w[i].number[j] = sign;
            w[i].number_reverse[sign - 1] = j + 1;
        }

        scanf_s("%i", &amount);

        w[i].notch = new int[amount];
        w[i].notch_amount = amount;

        for (int j = 0; j < amount; j++) {

            scanf_s("%i", &sign);

            w[i].notch[j] = sign;

        }

    }

    scanf_s("%i", &l);

    int** reflektor = new int* [l];

    for (int i = 0; i < l; i++) {

        reflektor[i] = new int[n];

        for (int j = 0; j < n; j++) {

            scanf_s("%i", &sign);

            reflektor[i][j] = sign;

        }
    }



    int tasks_amount, w_amount, w_index, w_position, r_index;

    scanf_s("%i", &tasks_amount);

    for (int task = 0; task < tasks_amount; task++) {

        scanf_s("%i", &w_amount);

        Wirnik* w_new = new Wirnik[w_amount];
        int* spin = new int[w_amount];

        for (int i = 0; i < w_amount; i++) {

            scanf_s("%i", &w_index);
            scanf_s("%i", &w_position);

            w_new[i] = w[w_index];
            spin[i] = w_position - 1;

        }

        spin[0]++;

        scanf_s("%i", &r_index);

        crypting(w_new, reflektor[r_index], spin, w_amount, n);

        delete[] spin;
        delete[] w_new;
    }


    for (int i = 0; i < l; i++)
        delete[] reflektor[i];

    delete[] reflektor;
    delete[] w;

    return 0;
}





void crypting(Wirnik* w, int* reflektor, int* spin, int w_amount, int n) {

    int out, delta, sign;
    bool double_step = false;

    scanf_s("%i", &sign);


    while (sign != 0) {

        for (int i = 0; i < w_amount; i++) {

            if (i == 3)
                break;

            spin[i] = spin[i] % n;

        }


        out = sign - 1;


        for (int i = 0; i < w_amount; i++) {

            out = calculating_out(out, 0, spin[i], false, n);

            delta = w[i].number[out] - out - 1;

            out = calculating_out(out, delta, spin[i], true, n);

        }


        delta = reflektor[out] - out - 1;

        out = out + delta;


        for (int i = w_amount - 1; i >= 0; i--) {

            out = calculating_out(out, 0, spin[i], false, n);

            delta = w[i].number_reverse[out] - out - 1;

            out = calculating_out(out, delta, spin[i], true, n);

        }



        printf("%i ", out + 1);
        scanf_s("%i", &sign);

        double_step = spinning(spin, double_step, w, w_amount, n);

    }

    printf("\n");

}






int calculating_out(int out, int delta, int spin, bool minus_spin, int n) {

    if (minus_spin)
        spin *= (-1);

    out = out + delta + spin;

    if (out < 0)
        out = out + n;

    if (out > n - 1)
        out = out - n;

    return out;
}





bool spinning(int* spin, bool double_step, Wirnik* w, int w_amount, int n) {

    int spin_position, notch;

    spin[0]++;

    if (double_step) {

        spin[1]++;
        spin[2]++;

        spin_position = spin[1] + 2;
        spin_position = spin_position % n;

        for (int j = 0; j < w[1].notch_amount; j++) {

            notch = w[1].notch[j] % n;

            if (spin_position == notch) {

                double_step = true;
                break;

            }
            else
                double_step = false;
        }



    }
    else {

        spin_position = spin[0] + 1;
        spin_position = spin_position % n;

        if (w_amount > 1 && w[0].notch_amount > 0) {

            for (int i = 0; i < w[0].notch_amount; i++) {

                notch = w[0].notch[i] % n;

                if (spin_position == notch) {

                    spin[1]++;

                    if (w_amount > 2 && w[1].notch_amount > 0) {

                        spin_position = spin[1] + 2;
                        spin_position = spin_position % n;

                        for (int j = 0; j < w[1].notch_amount; j++) {

                            notch = w[1].notch[j] % n;

                            if (spin_position == notch) {

                                double_step = true;
                                break;

                            }
                        }
                    }
                    break;
                }

            }
        }
    }

    return double_step;

}
