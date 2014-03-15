#ifndef TESTCONTACTO_H_
#define TESTCONTACTO_H_

#define MOTOR_SPEED 5
#define MAX_TORQUE 5000
        
#include <list> 
#include <string> 

class TestContacto: public Test {
public:
	TestContacto()
	{		
	
	     b2Body* ground = NULL;
	     {
             	     b2BodyDef bd;
                     ground = m_world->CreateBody(&bd);

            	     b2EdgeShape shape;
	             shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
	             ground->CreateFixture(&shape, 0.0f);
	     }	
	     
	     contacto = false;
	     //creo dos engranajes pegados
	     b2Vec2 vec1(0,10);
	     Engranaje* engranaje1 = new Engranaje(vec1, m_world, 0, 2, true, false);
	     
	     b2Vec2 vec2(4,10);
	     Engranaje* engranaje2 = new Engranaje(vec2, m_world, 0, 2, true, false);
	     
	     b2Vec2 vec3(10,20);
	     Engranaje* engranaje3 = new Engranaje(vec3, m_world, 0, 2, true, false);

	     b2Vec2 vec4(0,0);
	     Engranaje* engranaje4 = new Engranaje(vec4, m_world, 0, 2, true, false);	     

	     b2Vec2 vec5(6,20);
	     Engranaje* engranaje5 = new Engranaje(vec5, m_world, 0, 2, true, false);
	     
	     b2Vec2 vec6(5,0);
	     Engranaje* engranaje6 = new Engranaje(vec6, m_world, 0, 2, true, false);
	     
	     lista.push_back(engranaje1);
	     lista.push_back(engranaje2);
	     lista.push_back(engranaje3);
	     lista.push_back(engranaje4);
	     lista.push_back(engranaje5);
	     lista.push_back(engranaje6);
	        

        }
        
	b2Body* crearCuerpo(float x, float y, float radio){
	          b2Body* body;
	          b2BodyDef bodyDef;
	          bodyDef.type = b2_dynamicBody;
	          bodyDef.position.Set(x,y);
	          b2FixtureDef fixtureDef;
	          fixtureDef.density = 1;
	          b2CircleShape circleShape;
	          circleShape.m_radius = radio;
	          fixtureDef.shape = &circleShape;
	          body = m_world->CreateBody( &bodyDef );
	          body->CreateFixture( &fixtureDef );
	          return body;
        }
        
        b2Body* crearSoporte(float x, float y, float radio){
	          b2Body* body;
	          b2BodyDef bodyDef;
	          bodyDef.type = b2_staticBody;
	          bodyDef.position.Set(x,y);
	          b2FixtureDef fixtureDef;
	          b2CircleShape circleShape;
	          circleShape.m_radius = radio;
	          b2PolygonShape pon;
	          fixtureDef.shape = &circleShape;
	          body = m_world->CreateBody( &bodyDef );
	          body->CreateFixture( &fixtureDef );
	          return body;
        }
	
	b2Body* crearBox(float x, float  y, float hx, float hy){
		 b2FixtureDef plataforma;
		 plataforma.density=1;
		 b2PolygonShape boxShape;
		 boxShape.SetAsBox(hx,hy);
		 plataforma.shape = &boxShape;
		 //Creo el cuerpo
		 b2BodyDef def;
		 def.type = b2_dynamicBody;
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&plataforma);
	
		 return body;	
	
	}
	
        //joint maker
        b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	          b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque, b2Vec2 anchor) {
	          b2RevoluteJointDef revoluteJointDef;
	          revoluteJointDef.bodyA = soporte;
	          revoluteJointDef.bodyB = cuerpo;
	          revoluteJointDef.collideConnected = false;
	          revoluteJointDef.localAnchorA.Set(0,0);
	          revoluteJointDef.localAnchorB.Set(anchor.x,anchor.y);
	          revoluteJointDef.enableMotor = habilitarMotor;
	          revoluteJointDef.motorSpeed = velocidadMotor;
	          revoluteJointDef.maxMotorTorque = maxTorque;
	          //No sé si este casteo es necesario.
	          b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	          return joint;

        }
        
        
        b2GearJoint* crearGearJoint(b2World* mundo, b2Body* bodyA, b2Body* bodyB,
		b2Joint* jointA, b2Joint* jointb, float ratio) {
		
		  b2GearJointDef gearJointDef;
	          gearJointDef.bodyA = bodyA;
	          gearJointDef.bodyB = bodyB;
	          gearJointDef.joint1 = jointA;
	          gearJointDef.joint2 = jointb;
	          gearJointDef.ratio = ratio;
	          //No sé si este casteo es necesario.
	          b2GearJoint* engranaje = (b2GearJoint*) mundo->CreateJoint( &gearJointDef );
	          return engranaje;

       }

       b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	          b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque) {
	          b2RevoluteJointDef revoluteJointDef;
	          revoluteJointDef.bodyA = soporte;
	          revoluteJointDef.bodyB = cuerpo;
	          revoluteJointDef.collideConnected = false;
         	  revoluteJointDef.localAnchorA.Set(0,0);
	          revoluteJointDef.localAnchorB.Set(0,0);
	          revoluteJointDef.enableMotor = habilitarMotor;
	          revoluteJointDef.motorSpeed = velocidadMotor;
	          revoluteJointDef.maxMotorTorque = maxTorque;
	          //No sé si este casteo es necesario.
	          b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	          return joint;

      }
        
        
	void Step(Settings* settings)
	{
		Test::Step(settings);
		m_debugDraw.DrawString(5, m_textLine, "Prueba de contacto entre cuerpos");

                for(b2Contact* contact = m_world->GetContactList(); contact; contact = contact->GetNext()){
                
                        void* data1 = contact->GetFixtureA()->GetBody()->GetUserData();
                        void* data2 = contact->GetFixtureB()->GetBody()->GetUserData();
                        
                        if (data1 && data2){
                                m_textLine+=15;
                                m_debugDraw.DrawString(5, m_textLine, "hay contacto"); 
                                Engranaje* gear1 = static_cast<Engranaje*> (data1);
                                Engranaje* gear2 = static_cast<Engranaje*> (data2);
                                gear1->tocarse(gear2, m_world); 
                                
                        }
                
                }             

	}

	static Test* Create()
	{
		return new TestContacto();
	}
        
        struct bodyJoint {
           b2Body* body;
           b2RevoluteJoint* joint;
        };
        
        bool contacto;
        
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
	                cuerpo->SetUserData(this);
	                this->soporte = crearSoporte(mundo);
	                this->sentidoAntihorario = sentidoAntihorario;
	                this->sentidoHorario = sentidoHorario;
	                this->mundo = mundo;
	                float motorSpeed = MOTOR_SPEED;
	                float maxTorque = MAX_TORQUE;
	                if (sentidoAntihorario){
		                  this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
				                  false, (-1)*MOTOR_SPEED, MAX_TORQUE);
	                }else{
		                this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
						                  false, MOTOR_SPEED, MAX_TORQUE);
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
	                  revoluteJointDef.enableMotor = habilitarMotor;
	                  revoluteJointDef.motorSpeed = velocidadMotor;
	                  revoluteJointDef.maxMotorTorque = maxTorque;
	                  //No sé si este casteo es necesario.
	                  b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	                  return joint;

              }         
              
               b2GearJoint* crearGearJoint(b2World* mundo, b2Body* bodyA, b2Body* bodyB,
		        b2Joint* jointA, b2Joint* jointb, float ratio) {
		
		          b2GearJointDef gearJointDef;
	                  gearJointDef.bodyA = bodyA;
	                  gearJointDef.bodyB = bodyB;
	                  gearJointDef.joint1 = jointA;
	                  gearJointDef.joint2 = jointb;
	                  gearJointDef.ratio = ratio;
	                  //No sé si este casteo es necesario.
	                  b2GearJoint* engranaje = (b2GearJoint*) mundo->CreateJoint( &gearJointDef );
	                  return engranaje;

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
              
              void tocarse(Engranaje* otroCuerpo, b2World* mundo) {
	                otroCuerpo->conectarA(this, mundo);
              }

              void conectarA(Engranaje* eng, b2World* mundo) {
	                b2Body* soporteEngranaje1 = eng->getSoporte();
	                b2Joint* jointEngranaje1 = eng->getJoint();
	                b2Body* miSoporte = this->soporte;
	                b2Joint* miJoint = this->rJoint;
	                crearGearJoint(mundo,soporteEngranaje1,miSoporte,jointEngranaje1,
			                miJoint, 1);

              }

        };        

        std::list<Engranaje*> lista;
	
};

#endif /* TESTCONTACTO_H_ */
