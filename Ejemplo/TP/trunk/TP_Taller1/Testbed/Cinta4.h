#ifndef CINTA4_H_
#define CINTA4_H_

#define MOTOR_SPEED 5
#define MAX_TORQUE 5000

#include <list>

class Cinta4: public Test {
public:
	Cinta4()
	{		
	
	     b2Body* ground = NULL;
	     {
             	     b2BodyDef bd;
                     ground = m_world->CreateBody(&bd);

            	     b2EdgeShape shape;
	             shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
	             ground->CreateFixture(&shape, 0.0f);
	     }	
 
            float ancho = 14;
            float alto = 2;
            int posX = -3;
            int posY = 15;
            int cantCuerpos = (int) (ancho/alto);
            int medio = (int) cantCuerpos/2;
            b2Body* p = NULL;
            b2RevoluteJoint* joint = NULL;
            b2RevoluteJoint* prev_joint = NULL;
            b2Body* prev_body = NULL;
            b2Body* b;
            Engranaje* engranaje = NULL;
            Engranaje* prev_engranaje = NULL;
            
            for (int i = 0; i < cantCuerpos; i++){
                
                float hy = alto/2;
                float pos = posX+alto*i;
                b2Vec2 posInicial(pos, posY);
                float radio = alto;

                engranaje = new Engranaje(b2Vec2(pos,posY),m_world, 0, alto, true, false);
                
                if (i == medio){
                        engranaje_Central = engranaje;                    
                }

                joint = engranaje->getJoint();
                
                if (p != NULL){
                        crearRevoluteJoint(m_world, engranaje->getCuerpo(), p, false, 5, 5000);
                }
                
                
                if (i < cantCuerpos-1){
                        float posX = pos + hy;
                        float hx = hy;
                        float hy = alto - 0.1f;
                        p = crearPlataforma(posX,posY,hx,hy);
                        crearRevoluteJoint(m_world, engranaje->getCuerpo(), p, false, 5, 5000);  
                }
               
                engranajes.push_back(engranaje);
                
            }
            
            
            //creo cuerpos dinamicos que caen sobre la cinta
            b2Body* pl = crearBox(-3,30,1,1);
            crearBox(5,30,1,1);
            
            //ESTO PARA PROBAR EL JOINT CON EL SOPORTE CENTRAL
            //crearRevoluteJoint(m_world, central, pl, false, 5, 5000);  
            crearBox(0,30,1,1);

            //le agrego correar
            conectarAMotor();
            
            girarEngranajesAlMismoLado();

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
        
        b2Body* crearPlataforma(float x, float y, float hx, float hy) {
		 b2FixtureDef plataforma;
		 plataforma.density=1;
		 b2PolygonShape boxShape;
		 boxShape.SetAsBox(hx,hy);
		 plataforma.shape = &boxShape;
		 //Creo el cuerpo
		 b2BodyDef def;
		 
		 def.type = b2_staticBody;
		 
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&plataforma);
		
		 //creo circulos en parte superior e inferior de la plataforma
		 
                 b2Body* circleSup = crearCuerpo(x,y,hx);
                 b2Body* circleInf = crearCuerpo(x,y,hx);
                 
                 b2RevoluteJoint* jointCS = crearRevoluteJoint(m_world, circleSup, body, false, 5, 5000, b2Vec2(0,hx));
                 b2RevoluteJoint* jointCI = crearRevoluteJoint(m_world, circleInf, body, false, 5, 5000, b2Vec2(0,-hx));
                 
                 bodyJoint b_j_CircleSup;
                 b_j_CircleSup.body = circleSup;
                 b_j_CircleSup.joint = jointCS;
                 
                 bodyJoint b_j_CircleInf;
                 b_j_CircleInf.body = circleInf;
                 b_j_CircleInf.joint = jointCI;
                 
                 body_joint_Rectangulos.push_back(b_j_CircleSup);
                 body_joint_Rectangulos.push_back(b_j_CircleInf);
                 
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

        //parte de la correa	
        b2Joint* putCorrea(b2World* mundo, b2Body* cuerpo1, b2Body* cuerpo2,
		b2Joint* joint1, b2Joint* joint2, float ratio){

		crearGearJoint(mundo, cuerpo1,cuerpo2,joint1,joint2,ratio);
	}
        
        void conectarAMotor(){
 
		//MOTOR
		//deberia decir CuerpoRotativo* motor = new Motor(balbalbl), por el momento pruebo asi
		//le pongo q el motor gire en sentido horario
		Engranaje motor(b2Vec2(0,0), m_world, 0, 2, true, false);
	
		//ahora agrego la correa al engranaje central de la cinta transportadora
		b2Body* soporteCentral = engranaje_Central->getSoporte();
		b2RevoluteJoint* j_central = engranaje_Central->getJoint();
		
		b2Body* soporteMotor = motor.getSoporte();
		b2RevoluteJoint* rJointMotor = motor.getJoint();
		rJointMotor->EnableMotor(true);
		
		putCorrea(m_world, soporteMotor, soporteCentral, rJointMotor, j_central, 1);
		
		//aca la parte que no se aun donde ponerla, porque cuando se conecta el motor al engranaje central
		//de alguna forma le tiene que pasar al central el sentido de giro, asi los otros engranajes
		//giran para el mismo lado.
		if (motor.getSentidoHorario()){
		        engranaje_Central->setSentidoHorario(false);
		        engranaje_Central->setSentidoAntihorario(true);
		}else{
		        engranaje_Central->setSentidoHorario(true);
		        engranaje_Central->setSentidoAntihorario(false);		        
		}
		
        
        }
        
        //una vez conectado al motor las giro para el mismo lado
        void girarEngranajesAlMismoLado(){
                
                list<Engranaje*>::iterator it = engranajes.begin();
                list<Engranaje*>::iterator end = engranajes.end();
                
                while (it != end){
                        Engranaje* engranaje = *it;
                        if (engranaje != engranaje_Central){
                                b2RevoluteJoint* joint = engranaje->getJoint();
                                joint->EnableMotor(true);
                                if (engranaje_Central->getSentidoHorario()){
                                        joint->SetMotorSpeed(MOTOR_SPEED);
                                        engranaje->setSentidoHorario(true);
                                        engranaje->setSentidoAntihorario(false); 
                                }else{
                                        joint->SetMotorSpeed((-1)*MOTOR_SPEED);
                                        engranaje->setSentidoHorario(true);
                                        engranaje->setSentidoAntihorario(false); 
                                }

                        }
                        it++;   
                } 
        
                //lo mismo para los bodies de los rectangulos
                
                list<bodyJoint>::iterator it_b = body_joint_Rectangulos.begin();
                list<bodyJoint>::iterator end_b = body_joint_Rectangulos.end();
                
                while (it_b != end_b){
                        bodyJoint body = *it_b;
                        b2RevoluteJoint* joint = body.joint;
                        joint->EnableMotor(true);
                        if (engranaje_Central->getSentidoHorario()){
                                joint->SetMotorSpeed((-1)*MOTOR_SPEED); //es distinto al anterior por el joint que tiene. 

                        }else{
                                joint->SetMotorSpeed(MOTOR_SPEED);
                        }
                        it_b++;
		}

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
				                  false, (-1)* MOTOR_SPEED, MAX_TORQUE);
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
        
	void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Prueba cinta");

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Cinta4();
	}
        
        struct bodyJoint {
           b2Body* body;
           b2RevoluteJoint* joint;
        };
       
        std::list<bodyJoint> body_joint;
        
        std::list<bodyJoint> body_joint_Rectangulos;
        
        Engranaje* engranaje_Central;
        
        std::list<Engranaje*> engranajes;
        
	
};

#endif /* CINTA4_H_ */
