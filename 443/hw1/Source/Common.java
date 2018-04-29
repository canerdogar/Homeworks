
import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * 
 */
public class Common {

	private static Common instance = null;

	public static Common getInstance() {
		if(instance == null) {
			instance = new Common();
		}
		return instance;
	}

	/**
	 * Default constructor
	 */
	public Common() {
	}

	public void init(int width,int height){

		windowWidth=width;
		windowHeight=height;
		//this.entities = new ArrayList<Entity>();
		this.traders = new ArrayList<Trader>();
		this.plot=new PricePlot();
		this.sellOrderFactory=new SellOrderFactory();
		this.buyOrderFactory=new BuyOrderFactory();
		this.orders=new ArrayList<Order>();
		this.Beginner=new ArrayList<ConMan>();
		this.Novice=new ArrayList<ConMan>();
		this.Master=new ArrayList<ConMan>();
		this.Expert=new ArrayList<ConMan>();
		this.ticker=new Ticker();

        File file = new File("configure.txt");
        try {
            Scanner sc = new Scanner(file);
            List<String> pars=new ArrayList<>();
            String temp=sc.nextLine();
            this.numOfTraders = Integer.parseInt(temp);
            for (int i=0;i<numOfTraders;i++){

            	for(int j=0;j<3;j++){

            		pars.add(sc.nextLine());
				}

                traders.add(new Trader(pars.get(2),pars.get(0),pars.get(1),i ));
            	pars.clear();
            }
			temp=sc.nextLine();
            for (int i=0;i<Integer.parseInt(temp);i++){

            	pars.add(sc.nextLine());
            	pars.add(sc.nextLine());
            	Beginner.add(   new BasicConMan(pars.get(1),pars.get(0)) );
				pars.clear();
			}

        }catch(Exception e){
            e.printStackTrace();
        }


		//entities.addAll(traders);

	}


    public int numOfTraders;



	/**
	 * 
	 */
	public int windowWidth;

	/**
	 * 
	 */
	public int windowHeight;

	/**
	 * 
	 */
	public PricePlot plot;

	/**
	 * 
	 */
	public Ticker ticker;

	/**
	 * 
	 */
	public List<Trader> traders;

	/**
	 * 
	 */
	public List<ConMan> Beginner;
	public List<ConMan> Novice;
	public List<ConMan> Master;
	public List<ConMan> Expert;



	/**
	 * 
	 */
	public List<Order> orders;

	//public List<Entity> entities;

	public SellOrderFactory sellOrderFactory;

	public BuyOrderFactory buyOrderFactory;

	/**
	 * 
	 */
	public void stepAllEntities() {

		//System.out.println(Beginner.size());

		List<ConMan> deletedConman=new ArrayList<>();

		for(int i=0;i<Beginner.size();i++){

			if(Beginner.get(i).getFortune() >= 2000 && Beginner.get(i).getFortune() < 3000){
				deletedConman.add(Beginner.get(i));
				Novice.add(  new Novice( Beginner.get(i) ) );
			}

		}

		for (int i=0;i<deletedConman.size();i++){

			Beginner.remove(deletedConman.get(i));

		}

		deletedConman.clear();

		/////////////////////

		for(int i=0;i<Novice.size();i++){

			if(Novice.get(i).getFortune() >= 3000 && Novice.get(i).getFortune() < 5000){
				deletedConman.add(Novice.get(i));
				Master.add(  new Master( Novice.get(i) ) );
			}

		}

		for (int i=0;i<deletedConman.size();i++){

			Novice.remove(deletedConman.get(i));

		}

		deletedConman.clear();

		///////////////////////

		for(int i=0;i<Master.size();i++){

			if(Master.get(i).getFortune() >= 5000){
				deletedConman.add(Master.get(i));
				Expert.add(  new Expert( Master.get(i) ) );
			}

		}

		for (int i=0;i<deletedConman.size();i++){

			Master.remove(deletedConman.get(i));

		}

		deletedConman.clear();

		//////////


		/*System.out.println( "Beginner "+( Beginner.size() ));
		System.out.println( "Novice "+( Novice.size() ));
		System.out.println( "Master "+( Master.size() ));
		System.out.println( "Expert "+( Expert.size() ));*/

		plot.step();
        for (Trader t:traders) {
            t.step();
        }
		for (Order o:orders) {
			o.step();
		}
		for(ConMan c:Beginner){
        	c.step();
		}

		for(ConMan c:Novice){
			c.step();
		}

		for(ConMan c:Master){
			c.step();
		}

		for(ConMan c:Expert){
			c.step();
		}

		ticker.step();

	}

}