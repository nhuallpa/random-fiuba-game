  #ifndef CUADRADO_H_
  #define CUADRADO_H_
  #define DEGTORAD 0.0174532925199432957f
  #define RADTODEG 57.295779513082320876f
    
  class CuadradoTest : public Test
    {
        public:
        CuadradoTest() { 
		
			int posX = 0;
			int posY = 10;
			float angle= 45.0;
			float masa = 32.0;
			int h=10;
			int w=10;


			m_world->SetGravity(b2Vec2(0.0f, -10.0f));
			b2Vec2 center = b2Vec2( posX+w/2, posY+h/2 );



			b2BodyDef myBodyDef;
			myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
			myBodyDef.position.Set(posX+w/2, posY+h/2); //set the starting position
			myBodyDef.angle = (angle * DEGTORAD); //set the starting angle


			b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);
	
			b2PolygonShape boxShape;

			boxShape.SetAsBox(h,w,center,angle * DEGTORAD);
  
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.shape = &boxShape;
			boxFixtureDef.density = masa;
			dynamicBody->CreateFixture(&boxFixtureDef);
			dynamicBody->SetTransform( dynamicBody->GetPosition(), angle );






			b2BodyDef myBodyDef1;
			myBodyDef1.type = b2_dynamicBody; //this will be a dynamic body
			myBodyDef1.position.Set(posX+5+w/2, posY+2+h/2); //set the starting position
			myBodyDef1.angle = (angle * DEGTORAD); //set the starting angle


			b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef1);
	
			b2PolygonShape boxShape1;

			boxShape1.SetAsBox(h,w,center,angle * DEGTORAD);
  
			b2FixtureDef boxFixtureDef1;
			boxFixtureDef1.shape = &boxShape;
			boxFixtureDef1.density = masa;
			dynamicBody1->CreateFixture(&boxFixtureDef1);
			dynamicBody1->SetTransform( dynamicBody1->GetPosition(), angle );


		
		} 
        
		void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
		}

        static Test* Create()
        {
            return new CuadradoTest;
        }
    };
  
  #endif