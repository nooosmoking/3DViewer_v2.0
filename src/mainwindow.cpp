#include "mainwindow.h"

#include <Qt3DRender/qrenderaspect.h>

#include <QFile>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QQuaternion>
#include <QString>
#include <QTextStream>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <iostream>

#include "./ui_mainwindow.h"
#include "model.h"

QString MainWindow::ReadFileContent(const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Не удалось открыть файл" << filePath;
    return QString();
  }
  QTextStream in(&file);
  QString content = in.readAll();
  file.close();

  return content;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), model_(new s21::Model) {
  ui->setupUi(this);
  setWindowTitle("3DViewer");
  qApp->setStyleSheet(ReadFileContent("./view/style.qss"));
  SetSettings3D();
}

void MainWindow::on_open_file_button_clicked() {
  QString qstr = QFileDialog::getOpenFileName(this, "Выбрать файл", "./objs",
                                              ".obj (*.obj)");
  if (!qstr.isEmpty()) {
    ClearInput();
    model_->Clear();
    model_->Load(qstr);

    view_.setRootEntity((static_cast<Qt3DCore::QEntity *>(model_)));
    view_.show();

    ui->file_name_label->setText(QString::fromStdString(model_->GetFileName()));
    ui->count_of_vertex->setText(QString::number(model_->GetCountVertices()));
    ui->count_of_facet->setText(QString::number(model_->GetCountFacets()));
  }
}

void MainWindow::SetSettings3D() {
  ui->widget_3d = QWidget::createWindowContainer(&view_, this);
  ui->widget_3d->setMinimumSize(QSize(601, 581));
  view_.defaultFrameGraph()->setClearColor(QColor::fromRgb(0, 0, 0));

  Qt3DRender::QCamera *camera = view_.camera();
  camera->lens()->setPerspectiveProjection(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  camera->setPosition(QVector3D(0, 20., 40.0f));
  camera->setViewCenter(QVector3D(0, 0, 0));
}

MainWindow::~MainWindow() {}

void MainWindow::on_move_x_box_valueChanged(double val) {
  model_->Move(val, 0, 0);
  ui->move_x_slider->setValue(val);
}

void MainWindow::on_move_y_box_valueChanged(double val) {
  model_->Move(0, val, 0);
  ui->move_y_slider->setValue(val);
}

void MainWindow::on_move_z_box_valueChanged(double val) {
  model_->Move(0, 0, val);
  ui->move_z_slider->setValue(val);
}

void MainWindow::ClearInput() {
  int val = 0;

  ui->move_x_slider->setValue(val);
  ui->move_y_slider->setValue(val);
  ui->move_z_slider->setValue(val);

  ui->rotate_x_slider->setValue(val);
  ui->rotate_y_slider->setValue(val);
  ui->rotate_z_slider->setValue(val);

  ui->scale_box->setValue((double)val);
}
void MainWindow::on_rotate_x_box_valueChanged(double val) {
  model_->Rotate(val, 0, 0);
  ui->rotate_x_slider->setValue(val);
}

void MainWindow::on_rotate_y_box_valueChanged(double val) {
  model_->Rotate(0, val, 0);

  ui->rotate_y_slider->setValue(val);
}

void MainWindow::on_rotate_z_box_valueChanged(double val) {
  model_->Rotate(0, 0, val);

  ui->rotate_z_slider->setValue(val);
}

void MainWindow::on_move_x_slider_valueChanged(int val) {
  model_->Move(static_cast<double>(val), 0, 0);

  ui->move_x_box->setValue(static_cast<double>(val));
}

void MainWindow::on_move_y_slider_valueChanged(int val) {
  model_->Move(0, static_cast<double>(val), 0);
  ui->move_y_box->setValue(static_cast<double>(val));
}

void MainWindow::on_move_z_slider_valueChanged(int val) {
  model_->Move(0, 0, static_cast<double>(val));
  ui->move_z_box->setValue(static_cast<double>(val));
}

void MainWindow::on_rotate_x_slider_valueChanged(int val) {
  model_->Rotate(static_cast<double>(val), 0, 0);
  ui->rotate_x_box->setValue(static_cast<double>(val));
}

void MainWindow::on_rotate_y_slider_valueChanged(int val) {
  model_->Rotate(0, static_cast<double>(val), 0);
  ui->rotate_y_box->setValue(static_cast<double>(val));
}

void MainWindow::on_rotate_z_slider_valueChanged(int val) {
  model_->Rotate(0, 0, static_cast<double>(val));
  ui->rotate_z_box->setValue(static_cast<double>(val));
}

void MainWindow::on_scale_box_valueChanged(double val) {
  model_->Scale(val);
  int scale_slider_val = static_cast<int>(val * 10);
  ui->scale_slider->setValue(scale_slider_val);
}
void MainWindow::on_scale_slider_valueChanged(int val) {
  double scale_box_val = static_cast<double>(val) / 10.;
  model_->Scale(scale_box_val);

  ui->scale_box->setValue(scale_box_val);
}