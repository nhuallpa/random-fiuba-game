#ifndef SOGA3_H_
#define SOGA3_H_

#define RADTODEG 57.295779513082320876f
#define DEGTORAD 0.0174532925199432957f

class Soga3: public Test {
public:
        
	Soga3(){
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);
			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);

		}
		
		b2Body* link;
		b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape boxDef;
		b2CircleShape circleDef;
		b2RevoluteJointDef jd;
		jd.collideConnected = false;
		
		b2FixtureDef boxFixtureDef;
		
		//creo el primer cuerpo
                cuadrado = crearCuadradoEstatico();
                circulo = crearCirculoDinamico();
	        b2RopeJointDef j;
	        j.collideConnected = true;
                j.bodyA=cuadrado; //define bodies
                j.bodyB=circulo;
                j.localAnchorA = b2Vec2(2,0.5); //define anchors
                j.localAnchorB = b2Vec2(0,2);
                j.maxLength= (circulo->GetPosition() - cuadrado->GetPosition()).Length();
                m_world->CreateJoint(&j);
	        //unirPorSoga(cuadrado, circulo);
		

	}	

       //A ESTO DE ACA NO LE DES BOLA, ES LO MISMO Q ESTA EN SOGA4        
       int32 calcularTamSoga(b2Body* A, b2Body* B){
	  b2Vec2 posA = A->GetPosition();
	  b2Vec2 posB = B->GetPosition();
	  int32 xA = posA.x;
	  int32 xB = posB.x;
	  int32 yA = posA.y;
	  int32 yB = posB.y;
	  
          int32 result = (int32) sqrt (pow(xB-xA, 2) + pow(yB-yA, 2));
	  return result;
	}
	
	b2Body* crearCirculoDinamico() {	
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(5, 30); //a little to the left
		b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = 2; //radius
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body
		return dynamicBody1;
	
	}
	
	b2Body* crearCuadradoEstatico() {	
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody; //this will be a dynamic body
		myBodyDef.position.Set(-10, 20); //a little to the left -10,20
		b2Body* staticBody1 = m_world->CreateBody(&myBodyDef);
		b2PolygonShape boxDef;
		boxDef.SetAsBox(2,0.5);
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &boxDef; //this is a pointer to the shape above
		staticBody1->CreateFixture(&myFixtureDef); //add a fixture to the body
		return staticBody1;
	
	}
	
	void unirPorSoga(b2Body* bodyA, b2Body* bodyB){
	
                b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape boxDef;
		b2CircleShape circleDef;
		b2RevoluteJointDef jd;
		jd.collideConnected = false;
		
		b2FixtureDef boxFixtureDef;
	        b2Body* link = cuadrado;
		//ahora creo la soga
		const int32 N = calcularTamSoga(bodyA, bodyB);
		float xBody = bodyA->GetPosition().x;	
		float yBody = bodyA->GetPosition().y;
		

  		
		for (int32 i = 1; i <= N; i++){

		     b2BodyDef bodyDef;
		     float posY;
		     float y;
		     
		     //if (bodyB->GetPosition().x < bodyA->GetPosition().x){
		     //    xBody = xBody-0.4;
		     //}else{
		     //    xBody = xBody+0.4;
                     //}
                     
		     if (bodyB->GetPosition().y < bodyA->GetPosition().y){
		         posY = yBody-i;//i
		         //yBody-=0.8f;
		
		     }else{
		         posY = yBody+i;
		         //yBody+=0.8f;
	
                     }
		     
		     //if (bodyB->GetPosition().y < bodyA->GetPosition().y){
		     //bodyDef.position.Set(xBody,yBody-i);
		     //}else{
		     // bodyDef.position.Set(xBody,yBody+i);
		     //}
		     
  
		     bodyDef.type = b2_dynamicBody;
		     bodyDef.position.Set(xBody,posY);//posY
		     		    		     		     
		     //calculo el angulo que forman los dos puntos
		     int32 xA = bodyA->GetPosition().x;
	             int32 xB = bodyB->GetPosition().x;
	             int32 yA = bodyA->GetPosition().y;
	             int32 yB = bodyB->GetPosition().y;
	             
		 
		     //float32 angulo = atan((yB-yA)/(xB-xA)) ;
		     //bodyDef.angle = -angulo;
		     
		     b2PolygonShape boxDef;
		     //b2CircleShape boxDef;

		    // b2Vec2 centro(0.1f,0.5f/2);
		    // boxDef.SetAsBox(0.1f,0.5f,centro,angulo*RADTODEG);
		     boxDef.SetAsBox(0.1,0.5);
		     //boxDef.m_radius = 0.2;
		     b2FixtureDef boxFixtureDef;
		     boxFixtureDef.shape = &boxDef;
		     boxFixtureDef.density = 20.0f;
		     boxFixtureDef.friction = 0.2f;
		     boxFixtureDef.filter.categoryBits = 0x0001;
		     boxFixtureDef.filter.maskBits = 0xFFFF & ~0x0002;
		     boxFixtureDef.restitution = 0.5f;
		     
		     b2Body* body = m_world->CreateBody(&bodyDef);
		     //body->SetTransform(body->GetPosition(), angulo);
		     body->CreateFixture(&boxFixtureDef);
		     
		     //hago el joint
                     b2Vec2 aux;
		     if (bodyB->GetPosition().y < bodyA->GetPosition().y){
	                aux = b2Vec2(xBody,posY+0.5);//posY+0.5 //   
		     }else{
		        aux = b2Vec2(xBody,posY-0.5);//-0.5
		     }   
		     //b2Vec2 anchor(xBody,y);
	             b2Vec2 anchor = aux;
	             
		     jd.Initialize(link, body, anchor);

		     m_world->CreateJoint(&jd);

                     body->ResetMassData();
                     
                     link = body;
		
		}
		
		b2Vec2 posB = circulo->GetPosition();
		
		b2Vec2 anchor(posB.x, posB.y);
		jd.Initialize(link,circulo,anchor);
		m_world->CreateJoint(&jd);
		//body->ResetMassData();	
	
	}
	
        void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
    
            //show some text in the main screen
            m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
            m_textLine += 15;
            

        }
	
	static Test* Create(){
	    return new Soga3();
	}
	
	b2RopeJointDef m_ropeDef;
	b2Joint* m_rope;
	b2Body* cuadrado;
	b2Body* circulo;
	
};

#endif /* SOGA3_H_ */
