#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Quaternion.h"

namespace engine {
	class Camera {
	private:
		Mat4 _viewMatrix;
		Mat4 _orthoProjMatrix;
		Mat4 _perspProjMatrix;
		Vec3 _eye;
		Vec3 _center;
		Vec3 _up;
		Vec3 _cameraPoint;

		Quaternion _cameraRotation;

		float _rotationSpeed;

	public:
		Camera(){ _rotationSpeed = 0.5f; _cameraRotation = Quaternion(); }
		~Camera(){}

		void setLookAt(Vec3 eye, Vec3 center, Vec3 up){
			_eye = eye;
			_center = center;
			_up = up;
		}



		void setOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ){
			_orthoProjMatrix = GetOrthoProjection(top, bottom, left, right, nearZ, farZ);
		}

		void setPerspProjection(float fovy, float aspect, float nearZ, float farZ){
			_perspProjMatrix = GetPerspProjection(fovy, aspect, nearZ, farZ);
		}

		void setRotationSpeed(float value){
			_rotationSpeed = value;
		}

		void draw(bool persp, GLuint VBOID, float RotationAngleX, float RotationAngleY, float zoom){

			Mat4 projectionMatrix;

			if(persp){
				projectionMatrix = _perspProjMatrix;
			}else{
				projectionMatrix = _orthoProjMatrix;
			}

			_viewMatrix = GetView(_eye + Vec3(0,0,zoom), _center, _up);

			Quaternion qX = Quaternion(RotationAngleY * _rotationSpeed, Y_AXIS);	
			Quaternion qY = Quaternion(RotationAngleX * _rotationSpeed, X_AXIS);


			_cameraRotation = (qX * qY) * _cameraRotation;

			_viewMatrix = _cameraRotation.getMatrix() * _viewMatrix;

			//Camera Position ..... maybe....
			Quaternion q = Quaternion(0, _eye.x, _eye.y, _eye.z + zoom);
			q = (_cameraRotation * q) *_cameraRotation.Inverse();
			q = q * Quaternion(0,0,0,-1);
			//std::cerr << "x: " << -q.y << " y: " << q.x << " z: " << -q.t << std::endl;
			_cameraPoint = Vec3(-q.y, q.x, -q.t);

			glBindBuffer(GL_UNIFORM_BUFFER, VBOID);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), _viewMatrix.matrix);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), projectionMatrix.matrix);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		Vec3 getEye(){
			return _eye;
		}

		Vec3 getCenter(){
			return _center;
		}

		Vec3 getUp(){
			return _up;
		}

		Vec3 cameraPoint(){
			return _cameraPoint;
		}

    Quaternion getCameraRotation(){
      return _cameraRotation;
    }

    void setCameraRotation(Quaternion q){
      _cameraRotation = q;
    }

	};
}

#endif //CAMERA_H