import javax.swing.*;
import java.lang.*;

/**
 * 
 */
public class HitCoinRunner {

	/**
	 * Default constructor
	 */
	public HitCoinRunner(int width, int height) {
		window = new JFrame();
		common=Common.getInstance();
		common.init(width,height);
		display=new Display(common);
		window.setTitle("Hitcoin");
		window.setSize(width, height);
		window.setResizable(false);
		window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		//data = new Data(width,height);
		//display = new Display(data);
		window.add(display);
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				window.setVisible(true);
			}
		});




	}

	/**
	 * 
	 */
	public JFrame window;

	/**
	 * 
	 */
	public Display display;

	/**
	 * 
	 */
	public Common common;

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		if (args.length < 2) {
			args = new String[] { "800", "800"};
		}
		int width = Integer.parseInt(args[0]);
		int height = Integer.parseInt(args[1]);

		HitCoinRunner hitCoinRunner = new HitCoinRunner(width, height);

		while(true) {
			hitCoinRunner.display.repaint();
			hitCoinRunner.common.stepAllEntities();
			try {
				Thread.sleep((long) 50);

			}catch(Exception e){

				e.printStackTrace();
			}
		}
	}

}