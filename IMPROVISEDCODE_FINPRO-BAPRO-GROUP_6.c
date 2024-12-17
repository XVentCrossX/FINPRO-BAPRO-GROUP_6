#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 1000
#define MAX_NAME_LENGTH 100
#define MIN_AGE 0


typedef enum {
    HEALTHY,
    AT_RISK,
    CRITICAL,
} HealthStatus;

typedef struct {
    char name[MAX_NAME_LENGTH]; //Added max name length
    int age;
    float weight;
    float height;
    int sysBP;
    int diaBP;
    int glucoseLVL;
    int HDLcholesterol;
    int LDLcholesterol;
    int triglycerides;
    float sleephours;
    float sedentaryhours;
    int exercisedays;
    float dailywaterintake;
    int alcoholbottles;
    int smoker;
} HealthData;

void inputdata(HealthData *person);
float calculateBMI(float weight, float height);
HealthStatus analyzeCholesterol(const HealthData *person);
void recommendDiet(const HealthData *person);
void recommendExercise(const HealthData *person);
void analyzeSleep(const HealthData *person);
void displayFullReport(const HealthData *person);
void specificEvaluation(const HealthData *person, int choice);

int main() {
    int num_patients, choice; //Change n into num_patients for readability
    HealthData *patients;

    printf("Enter the number of Patients: ");
    scanf("%d", &num_patients);

    // Dynamic memory allocation for patients
    patients = (HealthData *)malloc(num_patients * sizeof(HealthData));
    if (patients == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < num_patients; i++) {
        printf("\n--- Input Data for Patient %d ---\n", i + 1);
        inputdata(&patients[i]);
    }

    for (int i = 0; i < num_patients; i++) {
        printf("\n--- Evaluation for %s ---\n", patients[i].name);
        printf("1. Full Evaluation\n");
        printf("2. Specific Parameter Check\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            displayFullReport(&patients[i]);
        } else if (choice == 2) {
            printf("\nChoose a parameter to evaluate:\n");
            printf("1. BMI\n2. Blood Pressure\n3. Glucose Level\n4. Cholesterol\n5. Sleep\n");
            scanf("%d", &choice);
            specificEvaluation(&patients[i], choice);
        } else {
            printf("Invalid choice. Skipping evaluation for %s.\n", patients[i].name);
        }
    }

    // Free allocated memory
    free(patients);
    return 0;
}

void inputdata(HealthData *person) {
    printf("Enter name: ");
    scanf(" %99[^\n]", person->name);

    //Making sure the Age input is not 0
    do {
        printf("Enter your age (in years): ");
        scanf("%d", &person->age);
    } while (person->age == MIN_AGE);

    printf("Enter weight (kg): ");
    scanf("%f", &person->weight);

    printf("Enter height (m): ");
    scanf("%f", &person->height);

    printf("Enter your systolic Blood Pressure (the upper number on the blood pressure machine): ");
    scanf("%d", &person->sysBP);

    printf("Enter your diastolic Blood Pressure (the bottom number on the blood pressure machine): ");
    scanf("%d", &person->diaBP);

    printf("Enter your glucose level (mg/dL) (average level is between 70 to 100): ");
    scanf("%d", &person->glucoseLVL);

    printf("Enter your HDL(High-density lipoprotein ) cholesterol (mg/dL) (average minimum HDL lvl for a person is 60):");
    scanf("%d", &person->HDLcholesterol);

    printf("Enter your LDL(Low-density lipoprotein ) cholesterol (mg/dL) (average good LDL lvl for a person is 100): ");
    scanf("%d", &person->LDLcholesterol);

    printf("Enter your triglycerides amount in your body (Triglycerides are a type of fat (lipid) found in your blood)(mg/dL): ");
    scanf("%d", &person->triglycerides );

    printf("Enter the amount of hours you sleep per day: ");
    scanf("%f", &person->sleephours);

    printf("Enter the amount of hours you spent in sedentary (seated like in an office or in class) per day: ");
    scanf("%f", &person->sedentaryhours);

    printf("Enter the amount of days you exercise per week: ");
    scanf("%d", &person->exercisedays);

    printf("Enter your daily water intake (liters): ");
    scanf("%f", &person->dailywaterintake);

    printf("Enter your alcohol consumption (units per week)(10 units is the same as a 750ml bottle of wine at 12.5% ABV): ");
    scanf("%d", &person->alcoholbottles);

    printf("Are you a smoker? (0 = No, 1 = Yes): ");
    scanf("%d", &person->smoker);
}

float calculateBMI(float weight, float height) {
    return weight / (height * height);
}

HealthStatus analyzeCholesterol(const HealthData *person) {
    if (person->HDLcholesterol < 40 || person->LDLcholesterol > 160 || person->triglycerides > 200) {
        return CRITICAL;
    } else if (person->HDLcholesterol < 60 || person->LDLcholesterol > 100 || person->triglycerides > 150) {
        return AT_RISK;
    } else {
        return HEALTHY;
    }
}

void recommendDiet(const HealthData *person) {
    printf("\n--Diet Recommendations--\n");
    if (person->HDLcholesterol < 40 || person->LDLcholesterol > 130) {
        printf("- Eat vegetables like spinach, broccoli, and kale (rich in fiber).\n");
        printf("- Include fruits like apples, berries, and oranges (help lower your cholesterol).\n");
        printf("- Avoid red meat and fried foods.\n");
    }
    if (person->glucoseLVL > 125) {
        printf("- Eat plant based foods like Beans and lentils (help regulate your glucose levels).\n");
        printf("- Avoid sugary snacks and drinks (with a maximum a day being 25 grams of sugar. this includes the sugar in your food and drinks.).\n");
    }
    if (person->dailywaterintake < 2.0) {
        printf("- Increase your water intake to be at least 2 liters per day.\n");
    }
}

void recommendExercise(const HealthData *person) {
    printf("\n--Exercise Recommendations--\n");
    if (person->exercisedays < 3) {
        printf("- Start with light exercises like walking for 30 minutes daily.\n");
        printf("- Gradually increase to moderate activities like sports involving a lot of moving or cycling also works.\n");
    }
    if (calculateBMI(person->weight, person->height) > 25) {
        printf("- Consider adding cardio into your exercizes to burn body fat. we suggest on jogging or running and maybe do some very high mobility type of sports like basketball or badminton. ");
        printf("- if you are homebound we suggest doing squat jumping, burpees, jumping jacks, or use a treadmill if available. but if you also want to strengthen your muscle building consider calisthenics. ");
    }
    
    if (person->sedentaryhours > 8) {
        printf("- Take breaks to stretch and move every hour during sedentary activities.\n");
    }
}

void analyzeSleep(const HealthData *person) {
    printf("\n--Sleep Analysis--\n");
    if (person->sleephours < 6) {
        printf("- Sleep duration is insufficient. Aim for at least 7-8 hours of sleep daily.\n");
        printf("- Follow a consistent sleep schedule and reduce time on your phone or any electronics before bed.\n");
    } else {
        printf("- Your sleep duration is sufficient. keep it up!.\n");
    }
}

void specificEvaluation(const HealthData *person, int choice) {
    switch (choice) {
        case 1: {
            float bmi = calculateBMI(person->weight, person->height);
            printf("BMI: %.2f ", bmi);
            if (bmi < 18.5) {
                printf("(Underweight)\n");
            } else if (bmi < 25) {
                printf("(Normal weight)\n");
            } else if (bmi < 30) {
                printf("(Overweight)\n");
            } else {
                printf("(Obese)\n");
            }
            break;
        }
        case 2:
            printf("Blood Pressure: %d/%d ", person->sysBP, person->diaBP);
            if (person->sysBP > 130 || person->diaBP > 80) {
                printf("(High)\n");
            } else {
                printf("(Normal)\n");
            }
            break;
        case 3:
            printf("Glucose Level: %d mg/dL ", person->glucoseLVL);
            if (person->glucoseLVL > 125) {
                printf("(Pre-Diabetic or Diabetic)\n");
            } else {
                printf("(Normal)\n");
            }
            break;
        case 4:
            if (analyzeCholesterol(person) == CRITICAL) {
                printf("Cholesterol Levels: Critical Risk\n");
            } else if (analyzeCholesterol(person) == AT_RISK) {
                printf("Cholesterol Levels: At Risk\n");
            } else {
                printf("Cholesterol Levels: Healthy\n");
            }
            break;
        case 5:
            analyzeSleep(person);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void displayFullReport(const HealthData *person) {
    float bmi = calculateBMI(person->weight, person->height);
    HealthStatus cholesterolStatus = analyzeCholesterol(person);

    printf("BMI: %.2f ", bmi);
    if (bmi < 18.5) {
        printf("(Underweight)\n");
    } else if (bmi < 25) {
        printf("(Normal weight)\n");
    } else if (bmi < 30) {
        printf("(Overweight)\n");
    } else {
        printf("(Obese)\n");
    }

    printf("Blood Pressure: %d/%d ", person->sysBP, person->diaBP);
    if (person->sysBP > 130 || person->diaBP > 80) {
        printf("High (Please visit a doctor)\n");
    } else {
        printf("Normal\n");
    }

    printf("Glucose Level: %d mg/dL ", person->glucoseLVL);
    if (person->glucoseLVL > 125) {
        printf("(Pre-Diabetic or Diabetic)\n");
    } else {
        printf("(Normal)\n");
    }

    printf("Cholesterol Levels: ");

    switch (cholesterolStatus) {    //Use switch case rather than if else for this
        case CRITICAL: printf("Critical Condition (contact a doctor immediately)\n"); break;
        case AT_RISK: printf("At Risk\n"); break;
        case HEALTHY: printf("Healthy\n"); break;
    }

    analyzeSleep(person);
    recommendDiet(person);
    recommendExercise(person);

    printf("\n**Lifestyle Notes:**\n");
    if (person->smoker) {
        printf("- Consider quitting smoking for better health outcomes.\n");
    }
    if (person->alcoholbottles > 14) {
        printf("- Reduce alcohol consumption to less than 14 units (1.5 750 bottles) per week.\n");
    }
    if (person->dailywaterintake < 2.0) {
        printf("- Increase daily water intake to atleast 2 liters per day for maintaining hydration.\n"); //Added minimum water intake
    }
}