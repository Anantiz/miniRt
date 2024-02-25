#include <math.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
    double z;
} Vector3;

typedef struct {
    Vector3 center;
    double radius;
} Sphere;

typedef struct {
    Vector3 point;
    double distance;
    bool hasCollision; // Flag indicating whether collision occurred
} CollisionResult;

/*
Aint't that beautiful? (joke it's scary)

a=Dx2​+Dy2​+Dz2​

b=2×(Dx×(Ox−Cx)+Dy×(Oy−Cy)+Dz×(Oz−Cz))b=2×(Dx​×(Ox​−Cx​)+Dy​×(Oy​−Cy​)+Dz​×(Oz​−Cz​))

c=(Ox−Cx)2+(Oy−Cy)2+(Oz−Cz)2−R2c=(Ox​−Cx​)2+(Oy​−Cy​)2+(Oz​−Cz​)2−R2

*/
CollisionResult intersectSphere(Vector3 rayOrigin, Vector3 rayDirection, Sphere sphere) {
    CollisionResult result;
    result.hasCollision = 0; // Initialize collision flag to false

    // Compute vector from ray origin to sphere center
    Vector3 oc = {sphere.center.x - rayOrigin.x, sphere.center.y - rayOrigin.y, sphere.center.z - rayOrigin.z};

    // Compute coefficients of quadratic equation
    double a = Vector3_dot(rayDirection, rayDirection);
    double b = 2.0 * Vector3_dot(oc, rayDirection);
    double c = Vector3_dot(oc, oc) - (sphere.radius * sphere.radius);

    // Compute discriminant
    double discriminant = b * b - 4 * a * c;

    // If discriminant is negative, no collision
    if (discriminant < 0) {
        return result;
    }

    // Compute distances along ray to intersection points
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    // Check if either intersection point is in front of the ray
    if (t1 > 0 || t2 > 0) { // Not entierly accurate Don't use this , it's just for demonstration
        result.hasCollision = 1; // Set collision flag to true
        // Choose the intersection point closest to the ray origin
        result.distance = (t1 < t2) ? t1 : t2;
        // Compute the collision point
        result.point.x = rayOrigin.x + rayDirection.x * result.distance;
        result.point.y = rayOrigin.y + rayDirection.y * result.distance;
        result.point.z = rayOrigin.z + rayDirection.z * result.distance;
    }
    return result;
}

CollisionResult intersectCuboid(Vector3 rayOrigin, Vector3 rayDirection, Cuboid cuboid) {
    CollisionResult result;
    result.hasCollision = false; // Initialize collision flag to false

    // Calculate inverse direction components to avoid division
    Vector3 invDir = {1.0 / rayDirection.x, 1.0 / rayDirection.y, 1.0 / rayDirection.z};

    // Calculate t-values for each face of the cuboid
    double tmin = (cuboid.min.x - rayOrigin.x) * invDir.x;
    double tmax = (cuboid.max.x - rayOrigin.x) * invDir.x;
    double tymin = (cuboid.min.y - rayOrigin.y) * invDir.y;
    double tymax = (cuboid.max.y - rayOrigin.y) * invDir.y;

    // Swap tmin and tmax if needed to ensure tmin < tmax
    if (tmin > tmax) {
        double temp = tmin;
        tmin = tmax;
        tmax = temp;
    }
    // Swap tymin and tymax if needed to ensure tymin < tymax
    if (tymin > tymax) {
        double temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    // Update tmin and tmax based on y-axis intersections
    if ((tmin > tymax) || (tymin > tmax)) {
        return result; // No collision with y-faces
    }
    if (tymin > tmin) {
        tmin = tymin;
	}
    if (tymax < tmax) {
        tmax = tymax;
    }

    // Calculate tz values for z-axis intersections
    double tzmin = (cuboid.min.z - rayOrigin.z) * invDir.z;
    double tzmax = (cuboid.max.z - rayOrigin.z) * invDir.z;

    // Swap tzmin and tzmax if needed to ensure tzmin < tzmax
    if (tzmin > tzmax) {
        double temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    // Update tmin and tmax based on z-axis intersections
    if ((tmin > tzmax) || (tzmin > tmax)) {
        return result; // No collision with z-faces
    }

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    // Check if the collision point is in front of the ray
    if (tmin > 0) {
        result.hasCollision = true; // Set collision flag to true
        result.distance = tmin; // Set collision distance
        // Calculate collision point
        result.point.x = rayOrigin.x + rayDirection.x * tmin;
        result.point.y = rayOrigin.y + rayDirection.y * tmin;
        result.point.z = rayOrigin.z + rayDirection.z * tmin;
    }

    return result;
}
