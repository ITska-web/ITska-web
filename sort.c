#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 10
// Любой комментарий
// новый комментарий
char names[90][64] = {
    "Александр", "Сергей", "Максим", "Дмитрий", "Артем",
    "Егор", "Иван", "Никита", "Михаил", "Тимур",
    "Анна", "Елена", "Мария", "Ольга", "Татьяна",
    "Виктория", "Дарья", "Ксения", "Анастасия", "Полина",
    "Светлана", "Елизавета", "Юлия", "Надежда", "Катерина",
    "Владимир", "Павел", "Роман", "Григорий", "Леонид",
    "Станислав", "Арсений", "Андрей", "Виктор", "Ярослав",
    "София", "Вероника", "Радмила", "Лилия", "Кристина",
    "Алиса", "Диaнa", "Мелания", "Злата", "Людмила",
    "Евгения", "Галина", "Тамара", "Снежана", "Варвара",
    "Петр", "Савелий", "Денис", "Константин", "Николай",
    "Роман", "Яков", "Артемий", "Игорь", "Федор",
    "Тихон", "Василий", "Альберт", "Валерий", "Олег",
    "Саша", "Никита", "Пристас", "Джордан", "Космо",
    "Шерлок", "Наоми", "Грейс", "Серена", "Виктория",
    "Джулия", "Изабелла", "Алеа", "Лукреция", "Морис",
    "Бенжамин", "Арнольд", "Леон", "Симон", "Эмма",
    "Зинеда", "Науэль", "Нория", "Сельма", "Бреанна"};

struct Student
{
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(char name[64], int math, int phy, int inf)
{
    struct Student newStudent;
    int total;
    strcpy(newStudent.name, name);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}
void printStudentInfo(struct Student student)
{
    printf("%s, %d, %d, %d, %d\n", student.name, student.math, student.phy, student.inf, student.total);
}

void SelectSort(struct Student students[])
{
    struct Student buf;
    int min;
    for (int i = 0; i < N; i++)
    {
        min = i;
        for (int j = i + 1; j < N; j++)
        {
            if (students[j].total < students[min].total)
            {
                min = j;
            }
        }
        if (i != min)
        {
            buf = students[i];
            students[i] = students[min];
            students[min] = buf;
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        printStudentInfo(students[i]);
    }
}

void CountingSort(struct Student students[])
{
    int max = 300;
    int count[301];
    struct Student output[N];

    memset(count, 0, sizeof(count));

    for (int i = 0; i < N; i++)
    {
        count[students[i].total]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++)
    {
        while (count[i] > 0)
        {
            students[index].total = i;
            count[i]--;
            index++;
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        printStudentInfo(students[i]);
    }
}

void QuickSort(struct Student students[], int low, int high)
{
    if (low < high)
    {
        int pivot = students[high].total;
        int i = (low - 1);

        for (int j = low; j < high; j++)
        {
            if (students[j].total < pivot)
            {
                i++;
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
        struct Student temp = students[i + 1];
        students[i + 1] = students[high];
        students[high] = temp;
        int pi = i + 1;

        QuickSort(students, low, pi - 1);
        QuickSort(students, pi + 1, high);
    }
}

int main()
{
    srand(time(NULL));
    struct Student students[N];
    printf("Неотсортированный массив: \n");
    for (int i = 0; i < N; i++)
    {
        int math = random() % 101;
        int phy = random() % 101;
        int inf = random() % 101;
        students[i] = addStudent(names[rand() % 90], math, phy, inf);
        printStudentInfo(students[i]);
    }
    printf("/////////////////////////////////////////////////////////////\n");
    printf("SelectSort: \n");
    clock_t Selectstart = clock();
    SelectSort(students);
    clock_t Selectend = clock();
    printf("/////////////////////////////////////////////////////////////\n");

    double time_spent = (double)(Selectend - Selectstart) / (CLOCKS_PER_SEC);
    printf("Время работы алгоритма SelectSort: %f Размер данных: %d\n", time_spent, N);

    printf("/////////////////////////////////////////////////////////////\n");
    printf("CountingSort: \n");
    clock_t Countingstart = clock();
    CountingSort(students);
    clock_t Countingend = clock();
    printf("////////////////////////////////////////////////////////////\n");

    double time_speent = (double)(Countingend - Countingstart) / (CLOCKS_PER_SEC);
    printf("Время работы алгоритма CountingSort: %f Размер данных: %d\n", time_speent, N);

    printf("//////////////////////////////////////////////////////////////\n");
    printf("QuickSort: \n");
    clock_t Quickstart = clock();
    QuickSort(students, 0, N - 1);
    clock_t Quickend = clock();
    for (int i = N - 1; i >= 0; i--)
    {
        printStudentInfo(students[i]);
    }

    double time_speeent = (double)(Quickend - Quickstart) / (CLOCKS_PER_SEC);
    printf("Время работы алгоритма QuickSort: %f Размер данных: %d\n", time_speeent, N);
    printf("//////////////////////////////////////////////////////////\n");

    printf("Информация о процессоре:\n");
    system("grep -E 'model name|MHz' /proc/cpuinfo | awk -F': ' '{print $2}' | head -2");

    return 0;
}