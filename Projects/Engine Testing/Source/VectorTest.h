
#include "Engine.h"

namespace engine{

	class VectorTest : public Test{

	public:
		VectorTest() : Test("Vector Test"){}


		void test(){
			// Constructor
			TEST(Vec3VoidConstructor);
			TEST(Vec3FloatConstructor);
			TEST(Vec3FloatsConstructor);
			TEST(Vec3Vec3Constructor);
			// Operators
			TEST(Vec3EqualOperator);
			TEST(Vec3PlusEqualOperator);
			TEST(Vec3MinusEqualOperator);
			TEST(Vec3TimesEqualOperator);
			TEST(Vec3TimesEqualFloatOperator);
			TEST(Vec3DivideEqualOperator);
			TEST(Vec3DivideEqualFloatOperator);
			TEST(Vec3CompareEqualOperator);
			TEST(Vec3CompareDiferentOperator);
			TEST(Vec3CompareMinorOperator);
			TEST(Vec3CompareGreaterEqualOperator);
			TEST(Vec3CompareGreaterEqualOperator2);
			TEST(Vec3MinusOperator);
			TEST(Vec3MinusOperatorAlone);
			TEST(Vec3PlusOperator);
			TEST(Vec3TimesOperator);
			TEST(Vec3TimesFloatOperator);
			TEST(Vec3DivideOperator);
			TEST(Vec3DivideFloatOperator);
			// Normalize
			TEST(Vec3Normalize);
			// Operations
			TEST(FloatTimesVec3Operator);
		}

		void Vec3VoidConstructor() {
			Vec3 v = Vec3();
			CHECK(v.x == 0 && v.y == 0 && v.z == 0);
		}

		void Vec3FloatConstructor() {
			float a = 10;
			Vec3 v = Vec3(a);
			CHECK(v.x == a && v.y == a && v.z == a);
		}

		void Vec3FloatsConstructor() {
			float a = 10;
			float b = 4;
			float c = 2;
			Vec3 v = Vec3(a,b,c);
			CHECK(v.x == a && v.y == b && v.z == c);
		}

		void Vec3Vec3Constructor() {
			Vec3 v1 = Vec3(3);
			Vec3 v2 = Vec3(v1);
			CHECK(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
		}

		void Vec3EqualOperator() {
			Vec3 v1 = Vec3(3);
			Vec3 v2 = v1;
			CHECK(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
		}

		void Vec3PlusEqualOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			Vec3 v2 = Vec3(b);
			v2 += v1;
			CHECK(v2.x == (a+b) && v2.y == (a+b) && v2.z == (a+b));
		}

		void Vec3MinusEqualOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			Vec3 v2 = Vec3(b);
			v2 -= v1;
			CHECK(v2.x == (b-a) && v2.y == (b-a) && v2.z == (b-a));
		}

		void Vec3TimesEqualOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			Vec3 v2 = Vec3(b);
			v2 *= v1;
			CHECK(v2.x == (b*a) && v2.y == (b*a) && v2.z == (b*a));
		}

		void Vec3TimesEqualFloatOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			v1 *= b;
			CHECK(v1.x == (b*a) && v1.y == (b*a) && v1.z == (b*a));
		}

		void Vec3DivideEqualOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			Vec3 v2 = Vec3(b);
			v2 /= v1;
			CHECK(v2.x == (float)(b/a) && v2.y == (float)(b/a) && v2.z == (float)(b/a));
		}

		void Vec3DivideEqualFloatOperator() {
			float a = 3;
			float b = 2;
			Vec3 v1 = Vec3(a);
			v1 /= b;
			CHECK(v1.x == (a/b) && v1.y == (a/b) && v1.z == (a/b));
		}
		
		void Vec3CompareEqualOperator() {
			float a = 3;
			Vec3 v1 = Vec3(a);
			Vec3 v2 = Vec3(a);
			CHECK(v1 == v2);
		}

		void Vec3CompareDiferentOperator() {
			Vec3 v1 = Vec3(2);
			Vec3 v2 = Vec3(3);
			CHECK(v1 != v2);
		}

		void Vec3CompareMinorOperator() {
			Vec3 v1 = Vec3(2);
			Vec3 v2 = Vec3(3);
			CHECK(v1 < v2);
		}

		void Vec3CompareGreaterEqualOperator() {
			Vec3 v1 = Vec3(3);
			Vec3 v2 = Vec3(3);
			CHECK(v1 >= v2);
		}

		void Vec3CompareGreaterEqualOperator2() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = Vec3(3);
			CHECK(v1 >= v2);
		}
		/////
		void Vec3MinusOperator() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = Vec3(3);
			Vec3 v3 = v1 - v2;
			CHECK(v3.x == (v1.x - v2.x) && v3.y == (v1.y - v2.y) && v3.z == (v1.z - v2.z));
		}

		void Vec3MinusOperatorAlone() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = -v1;
			CHECK(v2.x == (-v1.x) && v2.y == (-v1.y) && v2.z == (-v1.z));
		}

		void Vec3PlusOperator() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = Vec3(3);
			Vec3 v3 = v1 + v2;
			CHECK(v3.x == (v1.x + v2.x) && v3.y == (v1.y + v2.y) && v3.z == (v1.z + v2.z));
		}

		void Vec3TimesOperator() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = Vec3(3);
			Vec3 v3 = v1 * v2;
			CHECK(v3.x == (v1.x * v2.x) && v3.y == (v1.y * v2.y) && v3.z == (v1.z * v2.z));
		}

		void Vec3TimesFloatOperator() {
			float s = 3;
			Vec3 v1 = Vec3(5);
			Vec3 v2 = v1 * s;
			CHECK(v2.x == (v1.x * s) && v2.y == (v1.y * s) && v2.z == (v1.z * s));
		}

		void Vec3DivideOperator() {
			Vec3 v1 = Vec3(5);
			Vec3 v2 = Vec3(3);
			Vec3 v3 = v1 / v2;
			CHECK(v3.x == (float)(v1.x / v2.x) && v3.y == (float)(v1.y / v2.y) && v3.z == (float)(v1.z / v2.z));
		}

		void Vec3DivideFloatOperator() {
			float s = 3;
			Vec3 v1 = Vec3(5);
			Vec3 v2 = v1 / s;
			CHECK(v2.x == (float)(v1.x / s) && v2.y == (float)(v1.y / s) && v2.z == (float)(v1.z / s));
		}

		void Vec3Normalize(){
			Vec3 v1 = Vec3(1, 2, 3);
			Vec3 v2 = v1;

			v1.Normalise();
			CHECK(v1.x == (float)(v2.x / len(v2)) && v1.y == (float)(v2.y / len(v2)) && v1.z == (float)(v2.z / len(v2)));

		}

		void FloatTimesVec3Operator() {
			float s = 3;
			Vec3 v1 = Vec3(5);
			Vec3 v2 = s * v1;
			CHECK(v2.x == (v1.x * s) && v2.y == (v1.y * s) && v2.z == (v1.z * s));
		}

	};
}