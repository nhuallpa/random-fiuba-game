  #ifndef CUADRADOAGUA_H_
  #define CUADRADOAGUA_H_
  #define DEGTORAD 0.0174532925199432957f
  #define RADTODEG 57.295779513082320876f
    
  class CuadradoConAguaTest : public Test
    {
        public:
        CuadradoConAguaTest() { 
		
			int posX = 0;
			int posY = 10;
			float angle= 45.0;
			float masa = 32.0;
			int h=10;
			int w=10;

			m_world->SetGravity(b2Vec2(0.0f, -10.0f));
			b2Vec2 center = b2Vec2( posX+w/2, posY+h/2 );
			angle = angle;
			masa = masa;

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


			// Ahora creo el agua
			
			center = b2Vec2( posX+w/2, posY-50 );
			
			b2PolygonShape waterShape;
			boxShape.SetAsBox(h*100,w*100,center,0);
			b2FixtureDef waterFixtureDef;
			waterFixtureDef.shape = &waterShape;
			waterFixtureDef.isSensor = true;


			b2BodyDef bd;
			bd.type = b2BodyType(0);
			bd.position.Set(-1.112629318237305e+01f, 1.750797271728516e+00f);
			bd.angle = 0.000000000000000e+00f;
			bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
			bd.angularVelocity = 0.000000000000000e+00f;
			bd.linearDamping = 0.000000000000000e+00f;
			bd.angularDamping = 0.000000000000000e+00f;
			bd.allowSleep = bool(4);
			bd.awake = bool(2);
			bd.fixedRotation = bool(0);
			bd.bullet = bool(0);
			bd.active = bool(32);
			bd.gravityScale = 1.000000000000000e+00f;
			b2Body* waterBody = m_world->CreateBody(&bd);


			b2FixtureDef fd;
			fd.friction = 2.000000029802322e-01f;
			fd.restitution = 0.000000000000000e+00f;
			fd.density = 2.000000000000000e+00f;
			fd.isSensor = bool(1);
			fd.filter.categoryBits = uint16(1);
			fd.filter.maskBits = uint16(65535);
			fd.filter.groupIndex = int16(0);
			b2PolygonShape shape;
			b2Vec2 vs[8];
			vs[0].Set(-5.544052124023438e-01f, -1.515119433403015e+00f);
			vs[1].Set(-5.544052124023438e-01f, 7.516476631164551e+00f);
			vs[2].Set(-4.341683959960938e+01f, 7.516476631164551e+00f);
			vs[3].Set(-4.341683959960938e+01f, -1.515119433403015e+00f);
			shape.Set(vs, 4);

			fd.shape = &shape;

			waterBody->CreateFixture(&fd);





		
		} 
        
		void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
		}

        static Test* Create()
        {
            return new CuadradoConAguaTest;
        }
    };
  
  #endif