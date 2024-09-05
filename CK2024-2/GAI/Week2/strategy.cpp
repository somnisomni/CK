#include <iostream>
using namespace std;

class ICameraInterface {
  public:
    virtual void takePicture() = 0;
};

class CameraA : public ICameraInterface {
  public:
    void takePicture() {
      cout << "Camera A taking picture" << endl;
    }
};

class CameraB : public ICameraInterface {
  public:
    void takePicture() {
      cout << "Camera B taking picture" << endl;
    }
};

class CameraMan {
  private:
    ICameraInterface *myCamera;

  public:
    CameraMan() { }

    void setCamera(ICameraInterface *camera) {
      myCamera = camera;
    }
    void useCamera() {
      if(myCamera == nullptr) {
        cout << "No camera set" << endl;
        return;
      }

      myCamera->takePicture();
    }
};

int main() {
  CameraMan *cameraMan = new CameraMan();
  CameraA *cameraA = new CameraA();
  CameraB *cameraB = new CameraB();

  cameraMan->setCamera(cameraA);
  cameraMan->useCamera();

  cameraMan->setCamera(cameraB);
  cameraMan->useCamera();

  delete cameraMan;
  delete cameraA;
  delete cameraB;
  return 0;
}
