
#include "Engine.h"
#include "GL/glew.h"
#include "GL/freeglut.h"

namespace engine{

	class MatrixTest : public Test{

	public:
		MatrixTest() : Test("Matrix Test"){}


		void test(){
			TEST(MatrixVoidConstructor);
			TEST(MatrixArrayConstructor);
			TEST(MatrixTranspose);
			TEST(MatrixTimesMatrixOperator);
			TEST(MatrixSetOperator);
			TEST(MatrixEqualsOperator);
			TEST(MatrixDifferentOperator);
			TEST(MatrixTimesVectorOperator);
			TEST(MatrixClean);
			TEST(MatrixFloatTranslation);
			TEST(MatrixVectorTranslation);
			TEST(MatrixFloatScale);
			TEST(MatrixFloatUniformScale);
			TEST(MatrixVectorScale);
			TEST(MatrixViewMatrix);
			TEST(MatrixOrthoProjection);
			TEST(MatrixPerspProjection);
		}

	void MatrixVoidConstructor() {
			Mat4 m = Mat4();
			CHECK(m.matrix[0] == 0 && 
            m.matrix[1] == 0 &&
            m.matrix[2] == 0 &&
            m.matrix[3] == 0 &&
            m.matrix[4] == 0 &&
            m.matrix[5] == 0 &&
            m.matrix[6] == 0 &&
            m.matrix[7] == 0 &&
            m.matrix[8] == 0 &&
            m.matrix[9] == 0 &&
            m.matrix[10] == 0 &&
            m.matrix[11] == 0 &&
            m.matrix[12] == 0 &&
            m.matrix[13] == 0 &&
            m.matrix[14] == 0 &&
            m.matrix[15] == 0 );
		}

    void MatrixArrayConstructor() {
      GLfloat matrix[] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f, 
                        13.0f, 14.0f, 15.0f, 16.0f };
      Mat4 m = Mat4(matrix);

      CHECK(m.matrix[0] == 1.0f &&
            m.matrix[1] == 2.0f &&
            m.matrix[2] == 3.0f &&
            m.matrix[3] == 4.0f &&
            m.matrix[4] == 5.0f &&
            m.matrix[5] == 6.0f &&
            m.matrix[6] == 7.0f &&
            m.matrix[7] == 8.0f &&
            m.matrix[8] == 9.0f &&
            m.matrix[9] == 10.0f &&
            m.matrix[10] == 11.0f &&
            m.matrix[11] == 12.0f &&
            m.matrix[12] == 13.0f &&
            m.matrix[13] == 14.0f &&
            m.matrix[14] == 15.0f &&
            m.matrix[15] == 16.0f );
		}

	void MatrixTranspose() {
		GLfloat matrix1[] = { 1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 16.0f };

		GLfloat matrix2[] = { 1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f };

		Mat4 m1 = Mat4(matrix1);

		Mat4 m2 = Mat4(matrix2);

		m1.Transpose();
			CHECK(m1 == m2);
		}
	

	void MatrixTimesMatrixOperator() {
		GLfloat matrix1[] = { 1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 16.0f };
	
		Mat4 m1 = Mat4(matrix1);

		GLfloat matrix2[] = { 17.0f, 18.0f, 19.0f, 20.0f,
							21.0f, 22.0f, 23.0f, 24.0f,
							25.0f, 26.0f, 27.0f, 28.0f,
							29.0f, 30.0f, 31.0f, 32.0f };

		Mat4 m2 = Mat4(matrix2);

		GLfloat matrix3[] = { 250.0f,  260.0f,  270.0f,  280.0f,
							618.0f,  644.0f,  670.0f,  696.0f,
							986.0f, 1028.0f, 1070.0f, 1112.0f,
							1354.0f, 1412.0f, 1470.0f, 1528.0f };

		Mat4 m3 = Mat4(matrix3);

		Mat4 m4 = m1 * m2;

			CHECK(m3 == m4);
		}

	void MatrixSetOperator() {
		GLfloat matrix1[] = { 1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f };

		Mat4 m1 = Mat4(matrix1);

		Mat4 m2 = m1;
			
			CHECK(m1 == m2);
		}

	void MatrixEqualsOperator() {
		GLfloat matrix1[] = { 1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f };


		Mat4 m1 = Mat4(matrix1);

		Mat4 m2 = Mat4(matrix1);

		GLfloat matrix2[] = { 1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 0.0f };

		Mat4 m3 = Mat4(matrix2);

		CHECK((m1 == m2) && !(m1 == m3));
		}

	void MatrixDifferentOperator() {
		GLfloat matrix1[] = { 1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 16.0f };


		Mat4 m1 = Mat4(matrix1);

		Mat4 m2 = Mat4(matrix1);


		GLfloat matrix2[] = { 1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 0.0f };

		Mat4 m3 = Mat4(matrix2);

		CHECK( (m1 != m3) && !(m1!=m2));

		}

	void MatrixTimesVectorOperator() {
		GLfloat matrix[] = { 1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f };

		Mat4 m = Mat4(matrix);

		Vec4 v1 = Vec4(7.0f, 8.0f, 9.0f, 10.0f);

		Vec4 v2 = Vec4(90.0f, 226.0f, 362.0f, 498.0f);

		Vec4 v3 = m * v1;	
			CHECK(v2 == v3);

		}

	void MatrixClean() {
		GLfloat matrix[] = { 1.0e-6f, 1.0e-6f, 1.0e-6f, 1.0e-6f, 
							1.0e-6f, 1.0e-6f, 1.0e-6f, 1.0e-6f, 
							1.0e-6f, 1.0e-6f, 1.0e-6f, 1.0e-6f, 
							1.0e-6f, 1.0e-6f, 1.0e-6f, 1.0e-6f};


		Mat4 m = Mat4(matrix);

		m.Clean();


		CHECK(m.matrix[0] == 0 &&
			m.matrix[1] == 0 &&
			m.matrix[2] == 0 &&
			m.matrix[3] == 0 &&
			m.matrix[4] == 0 &&
			m.matrix[5] == 0 &&
			m.matrix[6] == 0 &&
			m.matrix[7] == 0 &&
			m.matrix[8] == 0 &&
			m.matrix[9] == 0 &&
			m.matrix[10] == 0 &&
			m.matrix[11] == 0 &&
			m.matrix[12] == 0 &&
			m.matrix[13] == 0 &&
			m.matrix[14] == 0 &&
			m.matrix[15] == 0);

		}

	void MatrixFloatTranslation() {
		GLfloat translation[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			5.0f, 5.0f, 5.0f, 1.0f
		};

		Mat4 t1(translation);
		
		Mat4 t2 = engine::GetTranslation(5.0f, 5.0f, 5.0f);

		CHECK(t1 == t2);

		}

	void MatrixVectorTranslation() {
		GLfloat translation[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			5.0f, 5.0f, 5.0f, 1.0f
		};

		Mat4 t1(translation);

		Vec3 v = Vec3(5.0f, 5.0f, 5.0f);

		Mat4 t2 = engine::GetTranslation(v);

		CHECK(t1==t2);
		}

	void MatrixFloatScale() {
		GLfloat scale[16] = {
			4.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 6.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 8.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Mat4 m1(scale);

		Mat4 m2 = engine::GetScale(4.0f, 6.0f, 8.0f);

		CHECK(m1 == m2);
	}
		
	void MatrixFloatUniformScale() {
		GLfloat scale[16] = {
			4.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 4.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 4.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Mat4 m1(scale);

		Mat4 m2 = engine::GetScale(4.0f);

		CHECK(m1 == m2);
		}

	void MatrixVectorScale() {
		GLfloat scale[16] = {
			4.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 6.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 8.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Mat4 m1(scale);
		
		Vec3 v = Vec3(4.0f, 6.0f, 8.0f);

		Mat4 m2 = engine::GetScale(v);

		CHECK(m1 == m2);
		}

	void MatrixViewMatrix() {
		Vec3 eye1 = Vec3(5.0f, 5.0f, 5.0f);
		Vec3 center1 = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 up1 = Vec3(0.0f, 1.0f, 0.0f);

		Mat4 m1 = engine::GetView(eye1, center1, up1);

		// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
		GLfloat ViewMatrix1[16] = {
			0.71f, -0.41f, 0.58f, 0.00f,
			0.00f, 0.82f, 0.58f, 0.00f,
			-0.71f, -0.41f, 0.58f, 0.00f,
			0.00f, 0.00f, -8.66f, 1.00f
		}; // Column Major

		Mat4 view1(ViewMatrix1);

		// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
		GLfloat ViewMatrix2[16] = {
			-0.71f, -0.41f, -0.58f, 0.00f,
			0.00f, 0.82f, -0.58f, 0.00f,
			0.71f, -0.41f, -0.58f, 0.00f,
			0.00f, 0.00f, -8.66f, 1.00f
		}; // Column Major

		Vec3 eye2 = Vec3(-5.0f, -5.0f, -5.0f);
		Vec3 center2 = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 up2 = Vec3(0.0f, 1.0f, 0.0f);

		Mat4 m2 = engine::GetView(eye2, center2, up2);

		Mat4 view2(ViewMatrix2);


		CHECK((m1 == view1) && (m2 == view2));

		}

	void MatrixOrthoProjection() {
		// Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
		GLfloat ProjectionMatrix[16] = {
			0.50f, 0.00f, 0.00f, 0.00f,
			0.00f, 0.50f, 0.00f, 0.00f,
			0.00f, 0.00f, -0.22f, 0.00f,
			0.00f, 0.00f, -1.22f, 1.00f
		}; // Column Major


		Mat4 proj(ProjectionMatrix);

		Mat4 m = engine::GetOrthoProjection(2.0f, -2.0f, -2.0f, 2.0f, 1.0f, 10.0f);

		CHECK(proj == m);
		}

	void MatrixPerspProjection() {
		// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
		GLfloat ProjectionMatrix[16] = {
			2.8f, 0.00f, 0.00f, 0.00f,
			0.00f, 3.73f, 0.00f, 0.00f,
			0.00f, 0.00f, -1.22f, -1.00f,
			0.00f, 0.00f, -2.22f, 0.00f
		}; // Column Major

		Mat4 proj(ProjectionMatrix);

		Mat4 m = engine::GetPerspProjection(30.0f, 640.0f / 480.0f, 1.0f, 10.0f);

		CHECK(proj == m);
		}

	};
}