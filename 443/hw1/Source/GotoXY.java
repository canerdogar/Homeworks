import java.util.Random;

public class GotoXY extends State {

    public GotoXY() {
    }

    @Override
    public void step(ConMan conman){

        getToken(conman);

        //System.out.println(conman.name+" in positionı" + " "+conman.position.x + " "+ conman.position.y);

        //System.out.printf("%s in farki %d %d\n",conman.name,(conman.position.getX() - conman.direction.getX()),(conman.position.getY() - conman.direction.getY()));
        //System.out.println(conman.name+" in farki" + " "+ (conman.position.getX() - conman.direction.getX()));
        //System.out.printf("%s in farki %f%n",conman.name,conman.position.distanceTo(conman.direction));
        if( --conman.timeToChange==0){
            //System.out.println("Degisti");
            Random rand=new Random();
            int randomNumber=rand.nextInt(3);
            if (randomNumber==0){
                conman.state=new Rest();
            }
            else if(randomNumber==1){
                conman.state=new ChaseClosest();
            }
            else if(randomNumber==2){
                conman.state=new Shake();
            }

            conman.timeToChange=50;

        }else{

            Position direction=Position.getUnit(conman.position,conman.direction);
            //double step=-5.0;
            conman.position= new Position(-direction.x  + conman.position.x, -direction.y  + conman.position.y);

        }



    }
}