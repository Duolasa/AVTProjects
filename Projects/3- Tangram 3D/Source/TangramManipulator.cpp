#include "TangramManipulator.h"



TangramManipulator::TangramManipulator()
{
}

TangramManipulator::~TangramManipulator()
{

}

void TangramManipulator::CreatePieces(){


  pieces[0].vertices.push_back( { { -0.525f, -0.525f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }});
  pieces[0].vertices.push_back( { { 0.525f, -0.525f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }});
  pieces[0].vertices.push_back( { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }});
  pieces[0].vertices.push_back({ { -0.525f, -0.525f, -0.1f, 1.0f }, { 0.0f, 0.0f, 0.50f, 1.0f } });
  pieces[0].vertices.push_back({ { 0.525f, -0.525f, -0.1f, 1.0f }, { 0.0f, 0.0f, 0.50f, 1.0f } });
  pieces[0].vertices.push_back({ { 0.0f, 0.0f, -0.1f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.50f } });
  pieces[0].indices.push_back(0);
  pieces[0].indices.push_back(1);
  pieces[0].indices.push_back(2);
  pieces[0].indices.push_back(3);
  pieces[0].indices.push_back(5);
  pieces[0].indices.push_back(4);

  pieces[0].indices.push_back(1);
  pieces[0].indices.push_back(0);
  pieces[0].indices.push_back(4);

  pieces[0].indices.push_back(4);
  pieces[0].indices.push_back(0);
  pieces[0].indices.push_back(3);

  pieces[0].indices.push_back(0);
  pieces[0].indices.push_back(5);
  pieces[0].indices.push_back(3);

  pieces[0].indices.push_back(0);
  pieces[0].indices.push_back(2);
  pieces[0].indices.push_back(5);

  pieces[0].indices.push_back(5);
  pieces[0].indices.push_back(2);
  pieces[0].indices.push_back(1);

  pieces[0].indices.push_back(1);
  pieces[0].indices.push_back(4);
  pieces[0].indices.push_back(5);
  pieces[0].createBuffers();



  pieces[1].vertices.push_back({ { 0.525f, -0.525f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } });
  pieces[1].vertices.push_back({ { 0.525f, 0.525f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } });
  pieces[1].vertices.push_back({ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } });
  pieces[1].vertices.push_back({ { 0.525f, -0.525f, -0.12f, 1.0f }, { 0.4f, 0.0f, 0.2f, 1.0f } });
  pieces[1].vertices.push_back({ { 0.525f, 0.525f, -0.12f, 1.0f }, { 0.4f, 0.0f, 0.2f, 1.0f } });
  pieces[1].vertices.push_back({ { 0.0f, 0.0f, -0.12f, 1.0f }, { 0.4f, 0.0f, 0.2f, 1.0f } });
  pieces[1].indices.push_back(0);
  pieces[1].indices.push_back(1);
  pieces[1].indices.push_back(2);
  pieces[1].indices.push_back(3);
  pieces[1].indices.push_back(5);
  pieces[1].indices.push_back(4);

  pieces[1].indices.push_back(1);
  pieces[1].indices.push_back(0);
  pieces[1].indices.push_back(4);

  pieces[1].indices.push_back(4);
  pieces[1].indices.push_back(0);
  pieces[1].indices.push_back(3);

  pieces[1].indices.push_back(0);
  pieces[1].indices.push_back(5);
  pieces[1].indices.push_back(3);

  pieces[1].indices.push_back(0);
  pieces[1].indices.push_back(2);
  pieces[1].indices.push_back(5);

  pieces[1].indices.push_back(5);
  pieces[1].indices.push_back(2);
  pieces[1].indices.push_back(1);

  pieces[1].indices.push_back(1);
  pieces[1].indices.push_back(4);
  pieces[1].indices.push_back(5);
  pieces[1].createBuffers();


  pieces[2].vertices.push_back({ { 0.525f, 0.525f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } });
  pieces[2].vertices.push_back({ { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } });
  pieces[2].vertices.push_back({ { 0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } });
  pieces[2].vertices.push_back({ { 0.525f, 0.525f, -0.12f, 1.0f }, { 0.1f, 0.2f, 1.0f, 1.0f } });
  pieces[2].vertices.push_back({ { 0.0f, 0.525f, -0.12f, 1.0f }, { 0.1f, 0.2f, 1.0f, 1.0f } });
  pieces[2].vertices.push_back({ { 0.2625f, 0.2625f, -0.12f, 1.0f }, { 0.1f, 0.2f, 1.0f, 1.0f } });
  pieces[2].indices.push_back(0);
  pieces[2].indices.push_back(1);
  pieces[2].indices.push_back(2);

  pieces[2].indices.push_back(3);
  pieces[2].indices.push_back(5);
  pieces[2].indices.push_back(4);

  pieces[2].indices.push_back(1);
  pieces[2].indices.push_back(0);
  pieces[2].indices.push_back(4);

  pieces[2].indices.push_back(4);
  pieces[2].indices.push_back(0);
  pieces[2].indices.push_back(3);

  pieces[2].indices.push_back(0);
  pieces[2].indices.push_back(5);
  pieces[2].indices.push_back(3);

  pieces[2].indices.push_back(0);
  pieces[2].indices.push_back(2);
  pieces[2].indices.push_back(5);

  pieces[2].indices.push_back(5);
  pieces[2].indices.push_back(2);
  pieces[2].indices.push_back(1);

  pieces[2].indices.push_back(1);
  pieces[2].indices.push_back(4);
  pieces[2].indices.push_back(5);
  pieces[2].createBuffers();


  pieces[3].vertices.push_back({ { -0.525f, 0.525f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } });
  pieces[3].vertices.push_back({ { -0.525f, 0.0f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } });
  pieces[3].vertices.push_back({ { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } });
  pieces[3].vertices.push_back({ { -0.525f, 0.525f, -0.08f, 1.0f }, { 0.2f, 0.3f, 0.0f, 1.0f } });
  pieces[3].vertices.push_back({ { -0.525f, 0.0f, -0.08f, 1.0f }, { 0.2f, 0.3f, 0.0f, 1.0f } });
  pieces[3].vertices.push_back({ { 0.0f, 0.525f, -0.08f, 1.0f }, { 0.2f, 0.3f, 0.0f, 1.0f } });
  pieces[3].indices.push_back(0);
  pieces[3].indices.push_back(1);
  pieces[3].indices.push_back(2);

  pieces[3].indices.push_back(3);
  pieces[3].indices.push_back(5);
  pieces[3].indices.push_back(4);

  pieces[3].indices.push_back(1);
  pieces[3].indices.push_back(0);
  pieces[3].indices.push_back(4);

  pieces[3].indices.push_back(4);
  pieces[3].indices.push_back(0);
  pieces[3].indices.push_back(3);

  pieces[3].indices.push_back(0);
  pieces[3].indices.push_back(5);
  pieces[3].indices.push_back(3);

  pieces[3].indices.push_back(0);
  pieces[3].indices.push_back(2);
  pieces[3].indices.push_back(5);

  pieces[3].indices.push_back(5);
  pieces[3].indices.push_back(2);
  pieces[3].indices.push_back(1);

  pieces[3].indices.push_back(1);
  pieces[3].indices.push_back(4);
  pieces[3].indices.push_back(5);
  pieces[3].createBuffers();


  pieces[4].vertices.push_back({ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.4f, 0.0f, 0.0f, 1.0f } });
  pieces[4].vertices.push_back({ { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.4f, 0.0f, 0.0f, 1.0f } });
  pieces[4].vertices.push_back({ { -0.2625f, -0.2625f, 0.0f, 1.0f }, { 0.4f, 0.0f, 0.0f, 1.0f } });
  pieces[4].vertices.push_back({ { 0.0f, 0.0f, -0.07f, 1.0f }, { 0.2f, 0.0f, 0.0f, 1.0f } });
  pieces[4].vertices.push_back({ { -0.2625f, 0.2625f, -0.07f, 1.0f }, { 0.2f, 0.0f, 0.0f, 1.0f } });
  pieces[4].vertices.push_back({ { -0.2625f, -0.2625f, -0.07f, 1.0f }, { 0.2f, 0.0f, 0.0f, 1.0f } });
  pieces[4].indices.push_back(0);
  pieces[4].indices.push_back(1);
  pieces[4].indices.push_back(2);

  pieces[4].indices.push_back(3);
  pieces[4].indices.push_back(5);
  pieces[4].indices.push_back(4);

  pieces[4].indices.push_back(1);
  pieces[4].indices.push_back(0);
  pieces[4].indices.push_back(4);

  pieces[4].indices.push_back(4);
  pieces[4].indices.push_back(0);
  pieces[4].indices.push_back(3);

  pieces[4].indices.push_back(0);
  pieces[4].indices.push_back(5);
  pieces[4].indices.push_back(3);

  pieces[4].indices.push_back(0);
  pieces[4].indices.push_back(2);
  pieces[4].indices.push_back(5);

  pieces[4].indices.push_back(5);
  pieces[4].indices.push_back(2);
  pieces[4].indices.push_back(1);

  pieces[4].indices.push_back(1);
  pieces[4].indices.push_back(4);
  pieces[4].indices.push_back(5);
  pieces[4].createBuffers();
  

  pieces[5].vertices.push_back({ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } });
  pieces[5].vertices.push_back({ { 0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } });
  pieces[5].vertices.push_back({ { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } });
  pieces[5].vertices.push_back({ { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } });
  pieces[5].vertices.push_back({ { 0.0f, 0.0f, -0.10f, 1.0f }, { 0.5f, 0.2f, 0.7f, 1.0f } });
  pieces[5].vertices.push_back({ { 0.2625f, 0.2625f, -0.10f, 1.0f }, { 0.5f, 0.2f, 0.70f, 1.0f } });
  pieces[5].vertices.push_back({ { 0.0f, 0.525f, -0.10f, 1.0f }, { 0.5f, 0.2f, 0.70f, 1.0f } });
  pieces[5].vertices.push_back({ { -0.2625f, 0.2625f, -0.10f, 1.0f }, { 0.5f, 0.2f, 0.70f, 1.0f } });
  pieces[5].indices.push_back(0);
  pieces[5].indices.push_back(1);
  pieces[5].indices.push_back(2);
  pieces[5].indices.push_back(2);
  pieces[5].indices.push_back(3);
  pieces[5].indices.push_back(0);
  pieces[5].indices.push_back(4);
  pieces[5].indices.push_back(6);
  pieces[5].indices.push_back(5);
  pieces[5].indices.push_back(6);
  pieces[5].indices.push_back(4);
  pieces[5].indices.push_back(7);

  pieces[5].indices.push_back(3);
  pieces[5].indices.push_back(2);
  pieces[5].indices.push_back(7);
  
  pieces[5].indices.push_back(2);
  pieces[5].indices.push_back(6);
  pieces[5].indices.push_back(7);

  pieces[5].indices.push_back(0);
  pieces[5].indices.push_back(7);
  pieces[5].indices.push_back(4);
  
  pieces[5].indices.push_back(3);
  pieces[5].indices.push_back(7);
  pieces[5].indices.push_back(0);

  pieces[5].indices.push_back(0);
  pieces[5].indices.push_back(5);
  pieces[5].indices.push_back(1);
  
  pieces[5].indices.push_back(4);
  pieces[5].indices.push_back(5);
  pieces[5].indices.push_back(0);

  pieces[5].indices.push_back(2);
  pieces[5].indices.push_back(1);
  pieces[5].indices.push_back(6);
 
  pieces[5].indices.push_back(1);
  pieces[5].indices.push_back(5);
  pieces[5].indices.push_back(6);
  pieces[5].createBuffers();
  

  pieces[6].vertices.push_back({ { -0.525f, -0.525f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.525f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.2625f, -0.2625f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.525f, -0.525f, -0.09f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.525f, 0.0f, -0.09f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.2625f, 0.2625f, -0.09f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } });
  pieces[6].vertices.push_back({ { -0.2625f, -0.2625f, -0.09f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } });
  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(2);
  pieces[6].indices.push_back(1);
  pieces[6].indices.push_back(2);
  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(3);
  pieces[6].indices.push_back(4);
  pieces[6].indices.push_back(5);
  pieces[6].indices.push_back(6);
  pieces[6].indices.push_back(6);
  pieces[6].indices.push_back(7);
  pieces[6].indices.push_back(4);

  pieces[6].indices.push_back(3);
  pieces[6].indices.push_back(7);
  pieces[6].indices.push_back(2);

  pieces[6].indices.push_back(2);
  pieces[6].indices.push_back(7);
  pieces[6].indices.push_back(6);

  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(4);
  pieces[6].indices.push_back(7);

  pieces[6].indices.push_back(3);
  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(7);

  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(1);
  pieces[6].indices.push_back(5);

  pieces[6].indices.push_back(4);
  pieces[6].indices.push_back(0);
  pieces[6].indices.push_back(5);

  pieces[6].indices.push_back(2);
  pieces[6].indices.push_back(6);
  pieces[6].indices.push_back(1);

  pieces[6].indices.push_back(1);
  pieces[6].indices.push_back(6);
  pieces[6].indices.push_back(5);
  pieces[6].createBuffers();


  pieces[7].vertices.push_back({ { -1.5f, -1.5f, -0.16f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].vertices.push_back({ { 1.5f, -1.5f, -0.16f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].vertices.push_back({ { 0.0f, 2.0f, -0.16f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].vertices.push_back({ { -1.5f, -1.5f, -0.2f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].vertices.push_back({ { 1.5f, -1.5f, -0.2f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].vertices.push_back({ { 0.0f, 2.0f, -0.2, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
  pieces[7].indices.push_back(0);
  pieces[7].indices.push_back(1);
  pieces[7].indices.push_back(2);
  pieces[7].indices.push_back(3);
  pieces[7].indices.push_back(5);
  pieces[7].indices.push_back(4);

  pieces[7].indices.push_back(1);
  pieces[7].indices.push_back(0);
  pieces[7].indices.push_back(4);

  pieces[7].indices.push_back(4);
  pieces[7].indices.push_back(0);
  pieces[7].indices.push_back(3);

  pieces[7].indices.push_back(0);
  pieces[7].indices.push_back(5);
  pieces[7].indices.push_back(3);

  pieces[7].indices.push_back(0);
  pieces[7].indices.push_back(2);
  pieces[7].indices.push_back(5);

  pieces[7].indices.push_back(5);
  pieces[7].indices.push_back(2);
  pieces[7].indices.push_back(1);

  pieces[7].indices.push_back(1);
  pieces[7].indices.push_back(4);
  pieces[7].indices.push_back(5);
  pieces[7].createBuffers();



  for (int i = 0; i < 8; i++)
  {
    pieces[i].transformationMatrix = matrixGenerator.GetIdentity();
  }

}

void TangramManipulator::DrawPieces(GLint UniformId){
  
  for (int i = 0; i < 8; i++){

    pieces[i].draw(UniformId);
  }

}


void TangramManipulator::FillWithIdentity(){
  for (int i = 0; i < 8; i++)
  {
    free(pieces[i].transformationMatrix);
    pieces[i].transformationMatrix = matrixGenerator.GetIdentity();
  }
}



void TangramManipulator::FillWithPresetPosition(){
  float z [] = { 0.0f, 0.0f, 1.0f };
  float x [] = { 1.0f, 0.0f, 0.0f };


  GLfloat* rotation = matrixGenerator.GetRotation(z, 90.0f);
  GLfloat* rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  GLfloat* translation = matrixGenerator.GetTranslation(-0.527f, 1.0f, 1.0f);
  GLfloat* multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[0].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, 180.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(0.527f, 1.0f, -1.0f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[1].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, 90.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(-0.29f, 0.7375f, 0.5f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[2].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, -45.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(0.53f, 0.25f, 1.0f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[3].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, 90.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(0.0f, 0.48f, -0.80f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[4].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, 00.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(-0.54f, 1.0f, -0.3f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[5].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);


  rotation = matrixGenerator.GetRotation(z, -90.0f);
  rotation2 = matrixGenerator.GetRotation(x, -90.0f);
  translation = matrixGenerator.GetTranslation(0.69f, 0.09f, 0.0f);
  multiplication = matrixGenerator.Multiply(translation, rotation);
  pieces[6].transformationMatrix = matrixGenerator.Multiply(rotation2, multiplication);
  free(rotation);
  free(translation);
  free(rotation2);
  free(multiplication);

}

