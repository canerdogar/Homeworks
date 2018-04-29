import java.util.Random;

public class Rest extends State {

    public Rest() {
    }

    @Override
    public void step(ConMan conman){

        if(--conman.timeToChange==0){

            Random rand=new Random();
            int randomNumber=rand.nextInt(3);
            if (randomNumber==0){
                conman.state=new ChaseClosest();
            }
            else if(randomNumber==1){
                conman.state=new GotoXY();
                Common common=Common.getInstance();
                double x=rand.nextInt( common.windowWidth -50) + 50;
                double y=rand.nextInt((3 * common.windowHeight) / 10 ) + common.windowHeight/5 ;
                //System.out.print(conman.name+" directionı "+x+" "+y);
                conman.direction=new Position(x,y);
            }
            else if(randomNumber==2){
                conman.state=new Shake();
            }

            conman.timeToChange=50;
        }



    }
}