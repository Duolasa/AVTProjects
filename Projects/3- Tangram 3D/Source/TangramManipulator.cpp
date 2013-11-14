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
  pieces[0].vertices.push_back({ { 0.0f, 0.0f, -0.1f, 1.0f }, { 0.0f, 0.0f, 0.5f, 0.50f } });
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
    frame[i] = 0.0f;
    pieces[i].beingAnimated = false;
  }

}

void TangramManipulator::DrawPieces(GLint UniformId){
  
  for (int i = 0; i < 8; i++){

    pieces[i].draw(UniformId);
  }

}


void TangramManipulator::ResetPieces(){
  for (int i = 0; i < 8; i++)
  {
    pieces[i].resetPiece();
    frame[i] = 0.0f;
    
  }
}

void TangramManipulator::animatePieces(){
  for (int i = 0; i < 8; i++)
  {
    if (pieces[i].beingAnimated){
      if (frame[i] > 100){
        pieces[i].beingAnimated = false;
      }
      else{
        pieces[i].changeIntermediateMatrix( frame[i]++ / 100.0f);
      }

    }
  }

}

void TangramManipulator::FillWithPresetPosition(int pieceID){
  switch (pieceID){
  case 0:{
    pieces[0].rotate(90, { 0, 1, 0, 0 });
    pieces[0].rotate(90, { 1, 0, 0, 0 });
    float movement0 [] = { 0.525f, 3.0f, 1.5f };
    pieces[0].move(movement0);
    pieces[0].beingAnimated = true;
    break;
    }

  case 1:{
    pieces[1].rotate(90, { 1, 0, 0, 0 });
    float movement1 [] = { -0.525f, -2.9f, 1.5f };
    pieces[1].move(movement1);
    pieces[1].beingAnimated = true;
    break;
    }

  case 2:{
    pieces[2].rotate(90, { 1, 0, 0, 0 });
    pieces[2].rotate(-90, { 0, 0, 1, 0 });
    float movement2 [] = { -0.27f, 2.5f, 1.76f };
    pieces[2].move(movement2);
    pieces[2].beingAnimated = true;
    break;
    }

  case 3:{
    pieces[3].rotate(90, { 1, 0, 0, 0 });
    pieces[3].rotate(-135, { 0, 0, 1, 0 });
    float movement3 [] = { 0.50f, 0.0f, 0.75f };
    pieces[3].move(movement3);
    pieces[3].beingAnimated = true;
    break;
    }

  case 4:{
    pieces[4].rotate(90, { 1, 0, 0, 0 });
    pieces[4].rotate(90, { 0, 0, 1, 0 });
    float movement4 [] = { 0.0f, -3.5f, 0.95f };
    pieces[4].move(movement4);
    pieces[4].beingAnimated = true;
    break;
    }

  case 5:{
    pieces[5].rotate(90, { 1, 0, 0, 0 });
    float movement5 [] = { -0.52f, 0.3f, 2.03f };
    pieces[5].move(movement5);
    pieces[5].beingAnimated = true;
    break;
    }

  case 6:{
    pieces[6].rotate(-90, { 1, 0, 0, 0 });
    pieces[6].rotate(90, { 0, 0, 1, 0 });
    float movement6 [] = { 0.69f, 2.3f, 0.6f };
    pieces[6].move(movement6);
    pieces[6].beingAnimated = true;
    break;
    }

  }
}

