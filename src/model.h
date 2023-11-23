#ifndef CPP_3D_VIEWER_MODEL_H_
#define CPP_3D_VIEWER_MODEL_H_

#include <Qt3DRender/qrenderaspect.h>

#include <QGuiApplication>
#include <QMouseEvent>
#include <QQuaternion>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DRender>
#include <fstream>
#include <iostream>
#include <string>

namespace s21 {

class Model : public Qt3DCore::QEntity {
 public:
  Model()
      : mesh_(new Qt3DRender::QMesh()),
        transform_(new Qt3DCore::QTransform()),
        material_(new Qt3DExtras::QPhongMaterial) {
    material_->setDiffuse(QColor(40, 255, 72));
    addComponent(material_);
    addComponent(transform_);
    SetLigthSettings();
  }

  void SetLigthSettings() {
    auto lightEntity =
        new Qt3DCore::QEntity(static_cast<Qt3DCore::QEntity*>(this));
    auto light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    auto lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(-40, 40, 40.0f));
    lightEntity->addComponent(lightTransform);
    lightEntity->setEnabled(true);

    auto lightEntity1 =
        new Qt3DCore::QEntity(static_cast<Qt3DCore::QEntity*>(this));
    auto light1 = new Qt3DRender::QDirectionalLight(lightEntity1);
    light1->setColor("white");
    light1->setIntensity(1);
    lightEntity1->addComponent(light1);
    auto lightTransform1 = new Qt3DCore::QTransform(lightEntity1);
    lightTransform1->setTranslation(QVector3D(40, -40, 40.0f));
    lightEntity1->addComponent(lightTransform1);
    lightEntity1->setEnabled(true);

    auto lightEntity2 =
        new Qt3DCore::QEntity(static_cast<Qt3DCore::QEntity*>(this));
    auto light2 = new Qt3DRender::QDirectionalLight(lightEntity2);
    light2->setColor("white");
    light2->setIntensity(1);
    lightEntity2->addComponent(light2);
    auto lightTransform2 = new Qt3DCore::QTransform(lightEntity2);
    lightTransform2->setTranslation(QVector3D(0, 0, -40.0f));
    lightEntity2->addComponent(lightTransform2);
    lightEntity2->setEnabled(true);
  }

  void Load(QString str) {
    filepath_ = str.toStdString();
    mesh_->setSource(QUrl::fromLocalFile(str));
    addComponent(mesh_);
  }

  std::string GetFileName() const {
    return std::filesystem::path(filepath_).filename().string();
  }

  int GetCountVertices() const {
    std::fstream f;
    std::string tmp;
    int count_veretices = 0;
    f.open(filepath_);
    if (f.is_open()) {
      while (std::getline(f, tmp)) {
        if (tmp[0] == 'v' && tmp[1] == ' ') {
          count_veretices++;
        }
      }
    }
    f.close();
    return count_veretices;
  }

  int GetCountFacets() const {
    std::fstream f;
    std::string tmp;
    int count_facets = 0;
    f.open(filepath_);
    if (f.is_open()) {
      while (std::getline(f, tmp)) {
        if (tmp[0] == 'f') {
          count_facets++;
        }
      }
    }
    f.close();
    return count_facets;
  }

  void Rotate(double x, double y, double z) {
    if (x != 0) {
      rotate_x_ = static_cast<float>(x);
    } else if (y != 0) {
      rotate_y_ = static_cast<float>(y);
    } else {
      rotate_z_ = static_cast<float>(z);
    }
    QQuaternion rotation =
        QQuaternion::fromEulerAngles(rotate_x_, rotate_y_, rotate_z_);
    transform_->setRotation(rotation);
  }

  void Move(double x, double y, double z) {
    if (x != 0) {
      move_x_ = static_cast<float>(x);
    } else if (y != 0) {
      move_y_ = static_cast<float>(y);
    } else {
      move_z_ = static_cast<float>(z);
    }
    transform_->setTranslation(QVector3D(move_x_, move_y_, move_z_));
  }

  void Scale(double val) { transform_->setScale3D(QVector3D(val, val, val)); }

  void Clear() {
    rotate_x_ = 0.;
    rotate_y_ = 0.;
    rotate_z_ = 0.;
    move_x_ = 0.;
    move_y_ = 0.;
    move_z_ = 0.;
    Rotate(rotate_x_, rotate_y_, rotate_z_);
    Move(move_x_, move_y_, move_z_);
    Scale(1.);
  }

  Qt3DCore::QTransform* GetTransform() { return transform_; }

 private:
  std::string filepath_;
  Qt3DRender::QMesh* mesh_;
  Qt3DCore::QTransform* transform_;
  Qt3DExtras::QPhongMaterial* material_;

  float rotate_x_ = 0.;
  float rotate_y_ = 0.;
  float rotate_z_ = 0.;

  float move_x_ = 0.;
  float move_y_ = 0.;
  float move_z_ = 0.;
};
}  // namespace s21

#endif  // CPP_3D_VIEWER_MODEL_H_
