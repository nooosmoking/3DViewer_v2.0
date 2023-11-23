#ifndef CPP_3D_VIEWER_MAINWINDOW_H_
#define CPP_3D_VIEWER_MAINWINDOW_H_

#include <QMainWindow>
#include <QString>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
 private slots:
  void on_move_x_box_valueChanged(double val);
  void on_move_y_box_valueChanged(double val);
  void on_move_z_box_valueChanged(double val);
  void on_rotate_x_box_valueChanged(double val);
  void on_rotate_y_box_valueChanged(double val);
  void on_rotate_z_box_valueChanged(double val);
  void on_scale_box_valueChanged(double val);

  void on_move_x_slider_valueChanged(int val);
  void on_move_y_slider_valueChanged(int val);
  void on_move_z_slider_valueChanged(int val);
  void on_rotate_x_slider_valueChanged(int val);
  void on_rotate_y_slider_valueChanged(int val);
  void on_rotate_z_slider_valueChanged(int val);
  void on_scale_slider_valueChanged(int val);

  void on_open_file_button_clicked();

 private:
  Ui::MainWindow* ui;
  s21::Model* model_;
  Qt3DExtras::Qt3DWindow view_;

  QString ReadFileContent(const QString& filePath);
  void SetSettings3D();
  void ClearInput();
};
#endif  // CPP_3D_VIEWER_MAINWINDOW_H_
