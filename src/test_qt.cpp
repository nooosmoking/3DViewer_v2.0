#include <gtest/gtest.h>
#include "model.h"
#include <QString>
using namespace s21;


TEST(MyTestSuite, TestLoader) {
    Model model;
    model.Load("cube.obj");
    ASSERT_EQ(model.GetCountFacets(),12);
}

TEST(MyTestSuite, TestRotate) {
    Model model;
    model.Load("cube.obj");
    ASSERT_EQ(model.GetCountFacets(), 12);

    // Apply rotation transformation
    double rotationAngle = 90.0;
    model.Rotate(rotationAngle,rotationAngle,rotationAngle);

    // Retrieve the rotation value
    QQuaternion appliedRotation = model.GetTransform()->rotation();

    // Compare the retrieved rotation value with the expected rotation value within a tolerance
    QQuaternion expectedRotation = QQuaternion::fromEulerAngles(rotationAngle, rotationAngle, rotationAngle);
    double tolerance = 1e-6;
    ASSERT_NEAR(appliedRotation.x(), expectedRotation.x(), tolerance);
    ASSERT_NEAR(appliedRotation.y(), expectedRotation.y(), tolerance);
    ASSERT_NEAR(appliedRotation.z(), expectedRotation.z(), tolerance);
    ASSERT_NEAR(appliedRotation.scalar(), expectedRotation.scalar(), tolerance);
}

TEST(MyTestSuite, TestScale) {
    Model model;
    model.Load("cube.obj");
    // Apply scale transformation
    double scaleValue = 0.5;
    model.Scale(scaleValue);

    // Retrieve the scale value
    QVector3D appliedScale = model.GetTransform()->scale3D();
    
    // Compare the retrieved scale value with the expected scale value
    ASSERT_EQ(appliedScale, QVector3D(scaleValue, scaleValue, scaleValue));
}

TEST(MyTestSuite, TestMove) {
    Model model;
    model.Load("cube.obj");

    // Move the model along x-axis
    model.Move(1.0, 0.0, 0.0);
    QVector3D updatedPosition = model.GetTransform()->translation();
    ASSERT_EQ(updatedPosition.x(), 1.0);
    ASSERT_EQ(updatedPosition.y(), 0.0);
    ASSERT_EQ(updatedPosition.z(), 0.0);

    // Move the model along y-axis
    model.Move(0.0, 2.0, 0.0);
    updatedPosition = model.GetTransform()->translation();
    ASSERT_EQ(updatedPosition.x(), 1.0);
    ASSERT_EQ(updatedPosition.y(), 2.0);
    ASSERT_EQ(updatedPosition.z(), 0.0);

    // Move the model along z-axis
    model.Move(0.0, 0.0, 3.0);
    updatedPosition = model.GetTransform()->translation();
    ASSERT_EQ(updatedPosition.x(), 1.0);
    ASSERT_EQ(updatedPosition.y(), 2.0);
    ASSERT_EQ(updatedPosition.z(), 3.0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}