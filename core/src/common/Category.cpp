#include "elan/common/Category.h"

namespace common
{
    Category determineCategory(int age)
    {
        if (age >= 3 && age <= 5)
            return Category::Age_3_5;
        if (age > 5 && age <= 6)
            return Category::Age_5_plus;
        if (age > 6 && age <= 7)
            return Category::Age_6_plus;
        if (age > 7 && age <= 10)
            return Category::Age_7_plus;
        if (age > 10 && age <= 12)
            return Category::Age_10_12;
        if (age > 12 && age <= 14)
            return Category::Age_14_plus;
        return Category::Age_16_plus;
    };
}