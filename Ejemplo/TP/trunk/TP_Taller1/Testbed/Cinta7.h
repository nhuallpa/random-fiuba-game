#ifndef Cinta7_H
#define Cinta7_H

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

class Cinta7 : public Test
{
public:
    Cinta7()
    {	     b2Body* ground = NULL;
	     {
             	     b2BodyDef bd;
                     ground = m_world->CreateBody(&bd);

            	     b2EdgeShape shape;
	             shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
	             ground->CreateFixture(&shape, 0.0f);
	     }	
       
 //some conveyor belts
 
        //body definition
        b2BodyDef myBodyDef;
        b2Body* staticBody = m_world->CreateBody(&myBodyDef);

       
 //some conveyor belts
        {
            int alto = 2;
            int ancho = 10; //10
            b2Vec2 pos(0,30);
            rectArriba = crearBox(pos.x,pos.y);
            //b2Body* bodyA = crearCircleD(-10,25,5); // -10,20,5
            //b2Body* a_s = crearCircleS(-10,25,0); //-10,20,0
            b2Vec2 pos1(pos.x-ancho,pos.y-alto);
            Engranaje* gear1 = new Engranaje(pos1, m_world, 0, alto, false, true);
            b2Vec2 pos2(pos.x+ancho,pos.y-alto);
            Engranaje* gear2 = new Engranaje(pos2, m_world, 0, alto, false, true);
            //b2Body* bodyB = crearCircleD(10,25,5); //10,20,5
            //b2Body* b_s = crearCircleS(10,25,0);   
            //crearRevoluteJoint(m_world,bodyA, a_s, 5, 5000);
            //crearRevoluteJoint(m_world,bodyB, b_s, 5, 5000);    
            rectAbajo = crearBox(0,pos.y-alto*2); //(0,alto*2)
            //some little boxes to liven things up
            {
                b2BodyDef rubbleBodyDef;
                rubbleBodyDef.type = b2_dynamicBody;
                b2PolygonShape rubbleShape;
                rubbleShape.SetAsBox(0.4f,0.5f);
                //b2CircleShape shape;
                //shape.m_radius = 1.0f;
                b2FixtureDef rubbleFixtureDef;
                //rubbleFixtureDef.friction = 0.9f;
                //rubbleFixtureDef.density = 3;//
                rubbleFixtureDef.shape = &rubbleShape;
                //for (int i = 0; i < 1; i++) {
                    //rubbleBodyDef.position.Set(1+ fmodf(i,5), i/6.0f );
                    rubbleBodyDef.position.Set(-5,40);
                    //rubbleBodyDef.position += b2Vec2(-18.5f, 32.5);
                    m_world->CreateBody(&rubbleBodyDef)->CreateFixture(&rubbleFixtureDef);
                //}
            }
        }   
        
       globoHelius = crearGloboDeHelio(5,0,0.5,0.1,1);
       crearCircleD(-10,50,1);
            
    }

	b2Body* crearCircleD(float x, float y, float radio){
		 b2FixtureDef c;
		 c.density = 1;
		 b2CircleShape circleShape;
		 circleShape.m_radius = radio;
		 c.shape = &circleShape;
		 //Creo el cuerpo
		 b2BodyDef def;
		 def.type = b2_dynamicBody;
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&c);
	
		 return body;	
	
	}
	
	b2Body* crearCircleS(float x, float y, float radio){
		 b2FixtureDef c;
		 c.density = 1;
		 b2CircleShape circleShape;
		 circleShape.m_radius = radio;
		 c.shape = &circleShape;
		 //Creo el cuerpo
		 b2BodyDef def;
		 def.type = b2_staticBody;
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&c);
	
		 return body;	
	
	}
	
	b2Body* crearBox(float x, float y){
	         b2FixtureDef c;
		 b2PolygonShape p;
		 p.SetAsBox(10.0f,0.00000000000000000000000000000000001f);
		 c.shape = &p;
		 //Creo el cuerpo
		 b2BodyDef def;
		 def.type = b2_staticBody;
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&c);
	
		 return body;	
	
	
	}

       b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	          b2Body* cuerpo, float velocidadMotor, float maxTorque) {
	          b2RevoluteJointDef revoluteJointDef;
	          revoluteJointDef.bodyA = soporte;
	          revoluteJointDef.bodyB = cuerpo;
	          revoluteJointDef.collideConnected = false;
         	  revoluteJointDef.localAnchorA.Set(0,0);
	          revoluteJointDef.localAnchorB.Set(0,0);
	          revoluteJointDef.enableMotor = true;
	          revoluteJointDef.motorSpeed = velocidadMotor;
	          revoluteJointDef.maxMotorTorque = maxTorque;
	          //No sÃ© si este casteo es necesario.
	          b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	          return joint;

      }
      
	b2Body* crearGloboDeHelio(float x, float y, float coefRes, float dens, float radio) {
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(x, y); //a little to the left
		b2Body* kinematicBody1 = m_world->CreateBody(&myBodyDef);
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = radio; //radius
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		myFixtureDef.density = dens;
		myFixtureDef.restitution = coefRes;
		kinematicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body	
		
		return kinematicBody1;
	}      
    void Step(Settings* settings)
    {
        m_debugDraw.DrawString(5, m_textLine, "prueba Cinta TT_TT");
        m_textLine += 15;

        Test::Step(settings);
        
                for(b2Contact* contact = m_world->GetContactList(); contact; contact = contact->GetNext()){
                
                        b2Body* a = contact->GetFixtureA()->GetBody();
                        b2Body* b = contact->GetFixtureB()->GetBody();
                        
                        b2Vec2 av = a->GetLinearVelocity();
                        b2Vec2 bv = b->GetLinearVelocity();
                        if (a == rectArriba){
                         
                                b->ApplyForceToCenter(b2Vec2(5,0)); 
                        }
                        if (b == rectArriba){
                        a->ApplyForceToCenter(b2Vec2(5,0));
                        }
                        
                        if (a == rectAbajo || b == rectAbajo){

 
                               b->ApplyForceToCenter(b2Vec2(-5,0));
                               a->ApplyForceToCenter(b2Vec2(-5,0));
                      }
                        
                       a->SetLinearVelocity(av);
                       b->SetLinearVelocity(bv);

                
                }    
                
            float force = globoHelius->GetMass()*(-9.8);
	    float impulso = globoHelius->GetMass()*4;
	    if(globoHelius->GetLinearVelocity().y < 4)            
            globoHelius->ApplyLinearImpulse(b2Vec2(0,impulso),globoHelius->GetWorldCenter());         
    }

    static Test* Create()
    {
        return new Cinta7;
    }


        //LO QUE CORRESPONDE A ENGRANAJE
        struct Engranaje{
	        b2RevoluteJoint* rJoint;
	        b2Vec2 posicion;
	        float angulo;
	        float radio;
	        b2Body* soporte;
	        b2World* mundo;
	        bool sentidoAntihorario;  
	        bool sentidoHorario;
	        b2Body* cuerpo;
	        
	        
	        Engranaje(b2Vec2 posInicial, b2World* mundo, float angulo, float radio,bool sentidoHorario, bool sentidoAntihorario){
	                this->posicion = posInicial;
	                this->angulo = angulo;
	                this->radio = radio;
	                this->cuerpo = crearCuerpo(mundo);
	                this->soporte = crearSoporte(mundo);
	                this->sentidoAntihorario = sentidoAntihorario;
	                this->sentidoHorario = sentidoHorario;
	                this->mundo = mundo;
	                float motorSpeed = MOTOR_SPEED;
	                float maxTorque = MAX_TORQUE;
	                if (sentidoAntihorario){
		                  this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
				                  false, (-1)*MOTOR_SPEED, 500000);
	                }else{
		                this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
						                  false, MOTOR_SPEED, 500000);
	                }	        
	        }
	        
	        b2Body* crearCuerpo(b2World* mundo){
	                  b2Body* body;
	                  b2BodyDef bodyDef;
	                  bodyDef.type = b2_dynamicBody;
	                  bodyDef.position.Set(this->posicion.x, this->posicion.y);
	                  b2FixtureDef fixtureDef;
	                  fixtureDef.density = DENSIDAD ;
	                  b2CircleShape circleShape;
	                  circleShape.m_radius = radio;
	                  fixtureDef.shape = &circleShape;
	                  body = mundo->CreateBody( &bodyDef );
	                  body->CreateFixture( &fixtureDef );
	                  return body;
               }

                b2Body* crearSoporte(b2World* mundo){
	                  b2Body* body;
	                  b2BodyDef bodyDef;
	                  bodyDef.type = b2_staticBody;
	                  bodyDef.position.Set(cuerpo->GetPosition().x, cuerpo->GetPosition().y);
	                  b2FixtureDef fixtureDef;
	                  b2CircleShape circleShape;
	                  circleShape.m_radius = 0;
	                  fixtureDef.shape = &circleShape;
	                  body = mundo->CreateBody( &bodyDef );
	                  body->CreateFixture( &fixtureDef );
	                  return body;
                }           
                
               b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	                  b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque) {
	                  b2RevoluteJointDef revoluteJointDef;
	                  revoluteJointDef.bodyA = soporte;
	                  revoluteJointDef.bodyB = cuerpo;
	                  revoluteJointDef.collideConnected = false;
                 	  revoluteJointDef.localAnchorA.Set(0,0);
	                  revoluteJointDef.localAnchorB.Set(0,0);
	                  revoluteJointDef.enableMotor = true;//habilitarMotor;
	                  revoluteJointDef.motorSpeed = velocidadMotor;
	                  revoluteJointDef.maxMotorTorque = maxTorque;
	                  //No sÃ© si este casteo es necesario.
	                  b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	                  return joint;

              }         
              
              b2Body* getCuerpo(){
                        return this->cuerpo;
              }       
              
              b2Body* getSoporte(){
                        return this->soporte;
              }
              
              b2RevoluteJoint* getJoint(){
                        return this->rJoint;
              }
              
              void setSentidoAntihorario(bool sentido){
                        this->sentidoAntihorario = sentido;
              }
              
              bool getSentidoAntihorario(){
                        return this->sentidoAntihorario;
              }
              
              void setSentidoHorario(bool sentido){
                        this->sentidoHorario = sentido;
              }
              
              bool getSentidoHorario(){
                        return this->sentidoHorario;
              }
        };
        
    ConveyorSegment m_circleConveyor;
    ConveyorSegment m_polygonConveyor;
    ConveyorSegment m_chainConveyor1, m_chainConveyor2;
    b2Body* m_circleBody;
    b2Body* rectArriba;
    b2Body* rectAbajo;
    b2Body* globoHelius;
};

#endif
