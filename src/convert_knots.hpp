#ifndef CONVERT_KNOTS_HPP
#define CONVERT_KNOTS_HPP

double knots_to_miles_per_minute(int knot) {
    // Conversion constants
    const double feet_per_knot = 6076.0;
    const double feet_per_mile = 5280.0;
    const double minutes_per_hour = 60.0;

    // Convert knots to feet per hour
    double feet_per_hour = knot * feet_per_knot;

    // Convert feet per hour to miles per hour
    double miles_per_hour = feet_per_hour / feet_per_mile;

    // Convert miles per hour to miles per minute
    double miles_per_minute = miles_per_hour / minutes_per_hour;

    return miles_per_minute;
}

#endif // CONVERT_KNOTS_HPP

