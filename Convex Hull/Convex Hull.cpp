#include <iostream>
#include <vector>

struct Point {
    int x, y;
};

std::vector<Point> hull;

bool isLeft(Point p1, Point p2, Point p) {
    return ((p.y - p1.y) * (p2.x - p1.x) -
        (p2.y - p1.y) * (p.x - p1.x)) > 0;
}

int lineDist(Point p1, Point p2, Point p) {
    return abs((p.y - p1.y) * (p2.x - p1.x) -
        (p2.y - p1.y) * (p.x - p1.x));
}

void insertExtreme(Point p) {
    for (int i = 0; i < int(hull.size()); i++) {
        if (p.x == hull[i].x && p.y == hull[i].y) {
            return;
        }
    }
    hull.push_back(p);
}

void convexHull(Point a[], int n) {
    // find extreme points
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].x < a[min_x].x)
            min_x = i;
        if (a[i].x > a[max_x].x)
            max_x = i;
        if (a[i].y < a[min_y].y)
            min_y = i;
        if (a[i].y > a[max_y].y)
            max_y = i;
    }
    insertExtreme(a[min_x]);
    insertExtreme(a[max_y]);
    insertExtreme(a[max_x]);
    insertExtreme(a[min_y]);

    // technically, delete points inside

    while (true) {
        // do for all lines in hull
        int changes = false;
        for (int i = 0; i < int(hull.size()); i++) {
            Point p1 = hull[i];
            Point p2 = hull[(i + 1) % int(hull.size())];
            //std::cout << "(" << p1.x << ", " << p1.y << ") (" << p2.x << ", " << p2.y << ")" << std::endl;

            // for all points in original array
            int max_dist = 0;
            int max_ind = 0;
            for (int j = 0; j < n; j++) {
                //std::cout << "(" << a[j].x << ", " << a[j].y << ")" << std::endl;
                int temp = lineDist(p1, p2, a[j]);
                if (isLeft(p1, p2, a[j]) && temp > max_dist) {
                    max_dist = temp;
                    max_ind = j;
                }
            }
            if (max_dist > 0) {
                changes = true;
                //std::cout << "insert " << a[max_ind].x << ", " << a[max_ind].y << std::endl;
                hull.insert(hull.begin() + i + 1, a[max_ind]);
            }
        }
        if (!changes) {
            // Filters points that might sit on an existing line
            for (int i = 0; i < int(hull.size()); i++) {
                Point p1 = hull[i];
                Point p3 = hull[(i + 1) % int(hull.size())];
                Point p2 = hull[(i + 2) % int(hull.size())];
                int max_dist = 0;
                int temp = lineDist(p1, p2, p3);
                if (isLeft(p1, p2, p3) && temp > max_dist) {
                    max_dist = temp;
                }

                if (max_dist == 0) {
                    hull.erase(hull.begin() + ((i + 1) % int(hull.size())));
                }
            }
            break;
        }
    }

    // Prints all corners of the hull
    for (int i = 0; i < int(hull.size()); i++) {
        std::cout << "(" << hull[i].x << ", " << hull[i].y << ")" << std::endl;
    }
}

int main() {
    Point points[] = { {1, 3}, {1, 7}, {2, 1}, {2, 4},
                        {1,14},{16,12}, {2, 4}, {5,10},
                        {6, 2}, {8,15}, {1, 4}, {6, 5},
                        {11,15},{16,3}, {2,24}, {6,10},
                        {6, 2}, {8,15}, {1, 4}, {6,15},
                        {1, 5}, {7,12},{22,24}, {6,19},
                        {2,10}, {1,10}, {3, 2}, {13,10} };
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
