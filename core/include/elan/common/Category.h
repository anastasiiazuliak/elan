#pragma once

namespace common
{
     enum class Category
    {
        Age_3_5,
        Age_5_plus,
        Age_6_plus,
        Age_7_plus,
        Age_10_12,
        Age_14_plus,
        Age_16_plus
    };

    Category determineCategory(int age);
}