

  ////body definition
  //  b2BodyDef myBodyDef;
  //  myBodyDef.type = b2_dynamicBody;
  //  
  //  //hexagonal shape definition
  //  b2PolygonShape polygonShape;
  //  b2Vec2 vertices[6];
  //  for (int i = 0; i < 6; i++) {
  //    float angle = -i/6.0 * 360 * DEGTORAD;
  //    vertices[i].Set(sinf(angle), cosf(angle));
  //  }
  //  vertices[0].Set( 0, 4 ); //change one vertex to be pointy
  //  polygonShape.Set(vertices, 6);
  //
  //  //fixture definition
  //  b2FixtureDef myFixtureDef;
  //  myFixtureDef.shape = &polygonShape;
  //  myFixtureDef.density = 1;
  //  
  //  //create dynamic body
  //  myBodyDef.position.Set(0, 10);
  //  body = m_world->CreateBody(&myBodyDef);
  //  body->CreateFixture(&myFixtureDef);