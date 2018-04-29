import java.util.Random;

public class ChaseClosest extends State {

    public ChaseClosest() {
    }

    @Override
    public void step(ConMan conman){

        getToken(conman);

        if(--conman.timeToChange==0){

            Random rand=new Random();
            int randomNumber=rand.nextInt(3);
            if (randomNumber==0){
                conman.state=new Rest();
            }
            else if(randomNumber==1){
                conman.state=new GotoXY();
                Common common=Common.getInstance();
                double x=rand.nextInt( common.windowWidth -30) + 30;
                double y=rand.nextInt((3 * common.windowHeight) / 10 ) + common.windowHeight/5 ;
                //System.out.print(conman.name+" directionı "+x+" "+y);
                conman.direction=new Position(x,y);
            }
            else if(randomNumber==2){
                conman.state=new Shake();
            }

            conman.timeToChange=50;
        }else{



            Common common=Common.getInstance();

            double minDistance=Double.MAX_VALUE;

            Order order=null;

            for (int i =0;i<common.orders.size();i++){

                if(common.orders.get(i).position.distanceTo(conman.position) < minDistance){

                    order=common.orders.get(i);

                }

            }

            if(order!=null){

                conman.direction=order.position;
                Position direction=Position.getUnit(conman.position,conman.direction);
                //double step=-5.0;
                conman.position= new Position(-direction.x  + conman.position.x, -direction.y  + conman.position.y);

            }




        }

    }
}