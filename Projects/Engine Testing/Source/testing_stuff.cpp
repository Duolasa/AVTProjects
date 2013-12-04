///////////////////////////////////////////////////////////////////////
//
// TestEngine, tests the classes from Engine Lib:
//
// - Vector class (Vec3, Vec4)
// - Matrix class (Mat4)
// - Quaternion class
//
// (c)2013	by Ruben Rebelo		nº55419
//			by Élvio Abreu		nº
//			by Rui Dias			nº67079
//			by Pedro Lousada	nº68582
//
///////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "VectorTest.h"
#include "MatrixTest.h"

using namespace engine;

int main(int argc, char* argv[])
{

	TestSuite testSuite = TestSuite("Engine");
	testSuite.addTest(new VectorTest());
  testSuite.addTest(new MatrixTest());
	testSuite.run();

}

///////////////////////////////////////////////////////////////////////