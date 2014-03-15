#ifndef CINTA2_H_
#define CINTA2_H_

#include <list>

class Cinta2: public Test {
public:
	Cinta2()
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
            for (int i = 0; i < cantCuerpos; i++){
                float hy = alto/2;
                float pos = posX+alto*i;
                b = crearCuerpo(pos, posY, alto);
                b2Body* soporte = crearSoporte(pos, posY, 0);
               
                joint = crearRevoluteJoint(m_world, soporte, b, false, 5, 5000);

                if (i == medio){
                        guardarSoporte(soporte);
                        guardarJointCentral(joint);
                        bodyCentral = b;
                    
                }
                prev_body = b;
                
                if (p != NULL){
                        crearRevoluteJoint(m_world, b, p, false, 5, 5000);
                }
                
                prev_joint = joint;
                
                if (i < cantCuerpos-1){
                        float posX = pos + hy;
                        float hx = hy;
                        float hy = alto - 0.1f;
                        p = crearPlataforma(posX,posY,hx,hy,true);
                        crearRevoluteJoint(m_world, b, p, false, 5, 5000);  
                }
                
                bodies.push_back(b);
                bodyJoint b_j;
                b_j.body = b;
                b_j.joint = joint;
                body_joint.push_back(b_j);
                
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
	
	void guardarSoporte(b2Body* soporte){
	    central = soporte;
	}
	
	void guardarJointCentral(b2RevoluteJoint* joint){
	    j_central = joint;
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
        
        b2Body* crearPlataforma(float x, float y, float hx, float hy, bool estatico) {
		 b2FixtureDef plataforma;
		 plataforma.density=1;
		 b2PolygonShape boxShape;
		 boxShape.SetAsBox(hx,hy);
		 plataforma.shape = &boxShape;
		 //Creo el cuerpo
		 b2BodyDef def;
		 
		 if (estatico) {
		        def.type = b2_staticBody;
		 }else{
		        def.type = b2_dynamicBody;
		 }
		 
		 def.position.Set(x, y);
		 b2Body* body = m_world->CreateBody(&def);
		 body->CreateFixture(&plataforma);
		
		 //creo circulos en parte superior e inferior de la plataforma
                 b2Body* circleSup = crearCuerpo(x,y,hx);
                 
                 b2Body* circleInf = crearCuerpo(x,y,-hx);
                 
                 b2RevoluteJoint* jointCS = crearRevoluteJoint(m_world, circleSup, body, false, 5, 5000, b2Vec2(0,hx));
                 b2RevoluteJoint* jointCI = crearRevoluteJoint(m_world, circleInf, body, false, 5, 5000, b2Vec2(0,-hx));
                 //agrego ambos circulos a la lista de bodies
                 bodies.push_back(circleSup);
                 bodies.push_back(circleInf);
                 
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
        void crearGear(b2Body* body, b2Body* prev_body, b2RevoluteJoint* joint, b2RevoluteJoint* prev_joint){
                  if (prev_body != NULL && prev_joint != NULL){
                        b2GearJointDef gear;
                        gear.bodyA = prev_body;
                        gear.bodyB = body;
                        gear.joint1 = prev_joint;
                        gear.joint2 = joint;
                        gear.collideConnected = false;
                        prev_joint->EnableMotor(true);
                        joint->EnableMotor(true);
                        b2GearJoint* gearJoint;
                        gearJoint = (b2GearJoint*) m_world->CreateJoint(&gear);
                  }
        }
        
        //parte de la correa	
        b2Joint* putCorrea(b2World* mundo, b2Body* cuerpo1, b2Body* cuerpo2,
		b2Joint* joint1, b2Joint* joint2, float ratio){

		crearGearJoint(mundo, cuerpo1,cuerpo2,joint1,joint2,ratio);
	}
        
        void conectarAMotor(){
                float motorSpeed = 5;
		float maxTorque = 5000;     
		//MOTOR
  		b2Body* motor = crearCuerpo(0, 0, 2);
		b2Body* soporteMotor = crearSoporte(0, 0, 0);
		b2Joint* rJointMotor = crearRevoluteJoint(m_world,soporteMotor, motor, true, motorSpeed, maxTorque);	
		//ahora agrego la correa al engranaje central de la cinta transportadora
		putCorrea(m_world, soporteMotor, central, rJointMotor, j_central, 1);
		
        
        }
        
        //una vez conectado al motor las giro para el mismo lado
        void girarEngranajesAlMismoLado(){
                
                list<bodyJoint>::iterator it = body_joint.begin();
                list<bodyJoint>::iterator end = body_joint.end();
                
                while (it != end){
                        bodyJoint body = *it;
                        if (body.body != bodyCentral){
                                b2RevoluteJoint* joint = body.joint;
                                joint->EnableMotor(true);
                                joint->SetMotorSpeed(-5); //mismo lado q motor
                        }
                        it++;   
                } 
        
                //lo mismo para los bodies de los rectangulos
                it = body_joint_Rectangulos.begin();
                end = body_joint_Rectangulos.end();
                
                while (it != end){
                        bodyJoint body = *it;
                        b2RevoluteJoint* joint = body.joint;
                        joint->EnableMotor(true);
                        joint->SetMotorSpeed(5); //mismo lado q motor
                        it++;
		}

        }
        
        
	void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Prueba cinta");

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Cinta2();
	}


        std::list<b2Body*> bodies;
        b2Body* central;
        b2Body* bodyCentral;
        b2RevoluteJoint * j_central;
        
        struct bodyJoint {
           b2Body* body;
           b2RevoluteJoint* joint;
        };
       
        std::list<bodyJoint> body_joint;
        
        std::list<bodyJoint> body_joint_Rectangulos;
        
	
};

#endif /* CINTA2_H_ */
