#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char country_name[70];
    double active_usage_per;
    char social_media[70];
    double active_users;
} social_media_info;

void menu(void)
{
    printf("\n\t\t------------- Menu to Use--------------\n");
    printf("\n\t\t1. View the file content on screen\n");
    printf("\n\t\t2. Load the file content to an array\n");
    printf("\n\t\t3. Get the country with the highest number of social media users\n");
    printf("\n\t\t4. Sort data by number of social media users\n");
    printf("\n\t\t5. Get social media data of a country\n");
    printf("\n\t\t6. Quit\n");
    printf("\n\t\t-----------------------------------------\n");
    printf("\n\t\tYour choice please:");
}

int load_file_content(FILE *fp, social_media_info *arr_sm_info)
{

    int i = 0, vergul;
    char line[70];
    char perc, enter, act_users[70];

    while (!feof(fp))
    {
        fgets(arr_sm_info[i].country_name, 70, fp);
        arr_sm_info[i].country_name[strlen(arr_sm_info[i].country_name) - 1] = '\0';
        fscanf(fp, "%lf", &arr_sm_info[i].active_usage_per);
        fscanf(fp, "%c%c", &perc, &enter);
        fgets(arr_sm_info[i].social_media, 70, fp);
        arr_sm_info[i].social_media[strlen(arr_sm_info[i].social_media) - 1] = '\0';
        fscanf(fp, "%s", act_users);
        for (int j = 0; j < strlen(act_users); j++)
        {
            if (act_users[j] == ',')
            {
                vergul = j;
            }
        }
        for (int j = vergul; j < strlen(act_users); j++)
        {
            act_users[j] = act_users[j + 1];
        }
        arr_sm_info[i].active_users = atof(act_users);
        fscanf(fp, "%c", &enter);
        fgets(line, 70, fp);
        i++;
    }

    return i;
}

social_media_info get_max(social_media_info *data, int size, social_media_info *country_high_sm_users)
{
    int i;
    int max = 0;
    for (i = 1; i < size; i++)
    {
        if (data[i].active_users > data[max].active_users)
        {
            max = i;
        }
    }
    *country_high_sm_users = data[max];
}

void display_file_content(FILE *fp)
{
    char line[70];
    while ((fgets(line, 70, fp)) != NULL)
    {
        printf("%s", line);
    }
    printf("\n");
}

void swap(social_media_info *x, social_media_info *y)
{
    social_media_info temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void sort_data_by_number_of_social_media_users(social_media_info *data, int size)
{
    int i, j, max;
    social_media_info temp;
    for (i = 0; i < size; i++)
    {
        max = i;
        for (j = i + 1; j < size; j++)
        {
            if (data[j].active_users > data[max].active_users)
            {
                max = j;
            }
        }
        if (max != i)
        {
            swap(&data[i], &data[max]);
        }
    }
}

social_media_info get_country_social_media_data(social_media_info *arr_sm_info, char *country_x, int n_countries, int *found)
{
    for (int i = 0; i < n_countries; i++)
    {
        if (strcmp(arr_sm_info[i].country_name, country_x) == 0)
        {
            *found = 1;
            return arr_sm_info[i];
        }
    }
}

int main(void)
{

    social_media_info arr_sm_info[100], target_country, country_high_sm_users;
    char country_x[70];
    int n_countries = 0;
    int choice, flag = 0, found = 0;

    FILE *fp = fopen("social_media.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t\tError opening the file\n");
        exit(1);
    }
    do
    {

        menu();
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            fseek(fp, 0, 0);
            display_file_content(fp);
            break;
        case 2:
            flag = 1;
            fseek(fp, 0, 0);
            n_countries = load_file_content(fp, arr_sm_info);
            printf("\n\t\tnumber of countries: %d\n", n_countries);
            break;
        case 3:
            if (flag == 0)
            {
                printf("\n\t\tOops! You have to load the file content first (Choice n2)\n");
                break;
            }
            get_max(arr_sm_info, n_countries, &country_high_sm_users);
            printf("\n\t\tThe country with the highest number of social media users is %s\n", country_high_sm_users.country_name);
        case 4:
            if (flag == 0)
            {
                printf("\n\t\tOops! You have to load the file content first (Choice n2)\n");
                break;
            }

            sort_data_by_number_of_social_media_users(arr_sm_info, n_countries);
            break;
        case 5:
            if (flag == 0)
            {
                printf("\n\t\tOops! You have to load the file content first (Choice n2)\n");
                break;
            }

            printf("\n\t\t Please Enter the name of the country:\t");
            scanf("%s", country_x);
            target_country = get_country_social_media_data(arr_sm_info, country_x, n_countries, &found);

            if (found == 0)
            {
                printf("\n\t\tOops!\tThe country you are looking for is not in the file\n");
                break;
            }

            printf("\n\t\t%s\n\t\t%.2lf%%\n\t\t%s\n\t\t%.2lfM\n", target_country.country_name, target_country.active_usage_per, target_country.social_media, target_country.active_users);
            break;
        case 6:
            printf("\n\t\t You decided to QUIT,...Bye!\n\n\t\t");
            break;
        default:
            printf("\n\t\tThat was a wrong choice!\n");
        }

    } while (choice != 6);

    fclose(fp);

    return 0;
}
