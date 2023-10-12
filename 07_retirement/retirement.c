#include<stdio.h>
#include<stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  
  for (int i = startAge; i < working.months + startAge; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, balance);
    balance += balance * working.rate_of_return + working.contribution;
  }

  for (int i = working.months + startAge; i < working.months + startAge + retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, balance);
    balance += balance * retired.rate_of_return + retired.contribution;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000.0;
  working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000.0;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
