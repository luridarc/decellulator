import java.util.*;
 
public enum Number { 
  ONE('1', #FF0000), 
  TWO('2', #00FF00), 
  THREE('3', #0000FF), 
  FOUR('4', #FFFF00), 
  FIVE('5', #00FFFF);
  //SIX('6', #440044);
  
  public final char value;
  public final color num_color;
  
  private Number(char _value, color _color){
    this.value = _value;
    this.num_color = _color;
  }
  
  public static Number GetRandom(){
    int number = (int) (Math.random() * Number.values().length) + 1;
    switch(number) {
      case 1:
        return Number.ONE;
      case 2:
        return Number.TWO;
      case 3:
        return Number.THREE;
      case 4:
        return Number.FOUR;
      case 5:
        return Number.FIVE;
      //case 6:
        //return Number.SIX;
      default:
        return null;
    }
  }
};

/**
* Cell is used as a single unit in the gameboard
*/
public class Cell{
  private Number cell_num;
  public void setCellNum(Number _cell_num){ this.cell_num = _cell_num; }
  public Number getCellNum(){ return this.cell_num; }
  
  private PVector pos;
  public void setPos(PVector _pos){ this.pos = _pos; }
  public PVector getPos(){ return this.pos; }
  
  public Cell(){}
  
  public Cell(int _x, int _y){
    super();
    this.setCellNum(Number.GetRandom());
    this.setPos(new PVector(_x, _y));
  }
  
  public void RenderCell(int _x, int _y, int _cell_width, int _cell_height){
    stroke(#393939);
    fill(#393939);
    rect(
      _x * _cell_width,
      _y * _cell_height, 
      _cell_width,
      _cell_height
    );
    stroke(#888888);
    fill(this.cell_num.num_color);
    rect(
      (_x * _cell_width) + 10,
      (_y * _cell_height) + 10, 
      _cell_width - 20,
      _cell_height - 20
    );
    fill(255);
    textSize(30);
    text(
      this.cell_num.value,
      _x * _cell_width + (_cell_width / 2),
      _y * _cell_height + (_cell_height / 2)
    );
  }
  
  public Number GetCellNum(){
    return this.cell_num;
  }
}

public class Board{
  private int b_width;
  private int b_height;
  private Cell[][] grid;
  
  public Board(int _width, int _height){
    this.b_width = _width;
    this.b_height = _height;
    this.grid = new Cell[_height][_width];
    this.PopulateGameboard();
  }
  
  public void PopulateGameboard(){
    for(int i = 0; i < b_height; i++){
      for(int j = 0; j < b_width; j++){
        grid[i][j] = new Cell();
        grid[i][j].setCellNum(Number.GetRandom());
        grid[i][j].setPos(new PVector(j, i));
      }
    }
  }
  
  public void RenderBoard(){
    for(int i = 0; i < b_height; i++){
      for(int j = 0; j < b_width; j++){
        grid[i][j].RenderCell(j, i, width / this.b_width, height / this.b_height);
      }
    }
  }
  
  public Cell[][] GetGrid(){
    return this.grid;
  }
  
  public int GetBoardWidth(){
    return this.b_width;
  }
  
  public int GetBoardHeight(){
    return this.b_height;
  }
  
  public Cell GetCell(int _x, int _y){
    return grid[_y][_x];
  }
  
  public void SetCell(int _x, int _y, Cell _prev){
    grid[_y][_x] = _prev;
  }
  
  public Cell GetRandom(){
    int temp_x = (int) (Math.random() * b_width);
    int temp_y = (int) (Math.random() * b_height);
    return grid[temp_x][temp_y];
  }
}

public class Game{
  private Board gameboard;
  private Player player;
  private long win_amt;
  
  public Game(){
    this.progress_time = 0;
    win_amt = 1500;
  }
  
  public long GetWinAmt(){
    return this.win_amt;
  }
  
  private long progress_time;
  
  Set<Set<Cell>> islands;
  
  public void InitIslands(){
     islands = new HashSet<Set<Cell>>();
  }
  
  public Set<Set<Cell>> GetIslands(){
    return this.islands;
  }
  
  public boolean IslandSelected(int _mouse_x, int _mouse_y){
    int x = GetXCellIndex(_mouse_x);
    int y = GetYCellIndex(_mouse_y);
    
    for(Set<Cell> each_island : islands){
      for(Cell each_cell : each_island){
        if((each_cell.getPos().x == x) && (each_cell.getPos().y == y)){
          return true;
        }
      }
    }
    return false;
  }
  
  public void InitBoard(int _width, int _height){
    this.gameboard = new Board(_width, _height);
    this.player = new Player();
    this.progress_time = 0;
  }
  
  public void IncrementProgress(long amt){
    if((this.progress_time + amt) > this.win_amt){
      this.progress_time = this.win_amt;
    } else {
      this.progress_time += amt;
    }
  }
  
  public void DecrementProgress(long amt){
    if((this.progress_time - amt) < 0){
      this.progress_time = 0;
    } else {
      this.progress_time -= amt;
    }
  }
  
  public long GetProgress(){
    return this.progress_time;
  }
  
  public Player GetPlayer(){
    return player;
  }
  
  public void RenderGame(){
    gameboard.RenderBoard();
  }
  
  public int GetXCellIndex(int _mouse_x){
    return _mouse_x / (width / gameboard.GetBoardWidth());
  }
  
  public int GetYCellIndex(int _mouse_y){
    return _mouse_y / (height / gameboard.GetBoardHeight());
  }
  
  public Board GetBoard(){
    return gameboard;
  }
  
  public void FindIslands(){
    InitIslands();
      for(int i = 0; i < gameboard.GetBoardHeight(); i++){
        for(int j = 0; j < gameboard.GetBoardWidth(); j++){
          Set<Cell> curr_island = GetIsland(j, i);
          if(curr_island.size() > 2){
            println("found one");
            islands.add(curr_island);
            for(Cell each : curr_island){
              println("   " + each.getPos().toString());
            }
          }
        }
      }
    
    PrintIslandData();
  }
  
  public void PrintIslandData(){
    println(islands.size());
  }
  
  public Set<Cell> GetIsland(int _cell_x, int _cell_y){
    int cell_x = _cell_x;
    int cell_y = _cell_y;
    
    Set<Cell> island = new HashSet<Cell>();
    island.add(gameboard.GetCell(cell_x, cell_y));
    
    SearchForIsland(cell_x, cell_y, island);
    
    return island;
  }
  
  private void SearchForIsland(int _x, int _y, Set<Cell> _island){
    
    try{
    // check right
      if(gameboard.GetCell( _x + 1, _y).GetCellNum().value == 
      gameboard.GetCell( _x, _y).GetCellNum().value){
        if(_island.add(gameboard.GetCell( _x + 1, _y))){
          SearchForIsland(_x + 1, _y, _island);
        }
      }
    } catch (Exception e){}
   
    // search left
    try{
      if(gameboard.GetCell( _x - 1, _y).GetCellNum().value == 
      gameboard.GetCell( _x, _y).GetCellNum().value){
        if(_island.add(gameboard.GetCell( _x - 1, _y))){
          SearchForIsland(_x - 1, _y, _island);
        }
      }
    } catch (Exception e){}
    
    // search up
    try{
      if(gameboard.GetCell( _x, _y + 1).GetCellNum().value == 
      gameboard.GetCell( _x, _y).GetCellNum().value){
        if(_island.add(gameboard.GetCell( _x, _y + 1))){
          SearchForIsland(_x, _y + 1, _island);
        }
      }
    } catch (Exception e){}
    
    // search down
    try{
      if(gameboard.GetCell( _x, _y - 1).GetCellNum().value == 
      gameboard.GetCell( _x, _y).GetCellNum().value){
        if(_island.add(gameboard.GetCell( _x, _y - 1))){
          SearchForIsland(_x, _y - 1, _island);
        }
      }
    } catch (Exception e){}
  }
  
  public int GetLeftIslandBound(Set<Cell> _island){
    int min = gameboard.GetBoardWidth();
    
    for(Cell each : _island){
      int _curr_x = (int) each.getPos().x;
      if(_curr_x < min){
        min = _curr_x;
      }
    }
    
    return min;
  }
  
  public int GetRightIslandBound(Set<Cell> _island){
    int max = 0;
    
    for(Cell each : _island){
      int _curr_x = (int) each.getPos().x;
      if(_curr_x > max){
        max = _curr_x;
      }
    }
    
    return max;
  }
  
  public int GetX_YMinBound(int _x, Set<Cell> _island){
    int min = gameboard.GetBoardHeight();
    
    for(Cell each : _island){
      if((int) each.getPos().x == _x){
        int _curr_y = (int) each.getPos().y;
        if(_curr_y < min){
          min = _curr_y;
        }
      }
    }
    
    return min;
  }
  
  public int GetX_YMaxBound(int _x, Set<Cell> _island){
    int max = 0;
    
    for(Cell each : _island){
      if((int) each.getPos().x == _x){
        int _curr_y = (int) each.getPos().y;
        if(_curr_y > max){
          max = _curr_y;
        }
      }
    }
    
    return max;
  }
  
  public void MakeIsland(){
    Number curr_value = null, forward_value;
    for(int i = gameboard.GetBoardHeight() - 1; i > -1; i--){
        for(int j = 0; j < gameboard.GetBoardWidth(); j++){
          
          curr_value = gameboard.GetCell(j, i).getCellNum();
          
          try{
            forward_value = gameboard.GetCell(j + 2, i).getCellNum();
            if(forward_value == curr_value){
              Cell new_cell = new Cell();
              new_cell.setCellNum(curr_value);
              new_cell.setPos(new PVector(j + 1, i));
              gameboard.SetCell(j + 1, i, new_cell);
              println("new cell at " + (j + 1) + ", " + i);
              return;
            }
          } catch (Exception e) {}
        }
      }
  }
  
  public void RenderHelper(){
    Set<Cell> island = (Set<Cell>) islands.toArray()[0];
    for(Cell each_cell : island){
      fill(#ffffff);
      stroke(#ffffff);
      ellipse(
        (int) (each_cell.getPos().x * (width / gameboard.GetBoardWidth())) + 20,
        (int) (each_cell.getPos().y * (height / gameboard.GetBoardHeight())) + 20,
        20,
        20
      );
    }
  }
}

public class Player{
  public long score;
  
  public Player(){
    score = 0;
  }
}

public void NewGame()
{
  last_success_time = 0;
  helped = false;
  time_update = millis();
  game_over = false;
  
  int WIDTH = 8;
  int HEIGHT = 7;
  
  bitmasher = new Game();
  bitmasher.InitBoard(WIDTH, HEIGHT);
  bitmasher.InitIslands();
  bitmasher.FindIslands();
}

Game bitmasher;
long last_success_time;
boolean helped;
long time_update;
boolean game_over;
long player_win_value;

public void setup(){
  size(displayWidth, displayWidth);
  background(0);
  NewGame();
  player_win_value = 1000;
}

public void draw(){
  bitmasher.RenderGame();
  
  //text(bitmasher.GetProgress(), 10, 60);
  fill(255);
  rect(0, 0,
    (int) ((((float) bitmasher.GetProgress() / bitmasher.GetWinAmt()) * width)),
    20
  );
  fill(#00ff00);
  rect(0, height - 20,
    (int) ((((float) bitmasher.GetPlayer().score / player_win_value) * width)),
    20
  );
  
  if(!game_over && ((millis() - last_success_time) > 3000)){
    bitmasher.RenderHelper();
    helped = true;
  }
  
  if(!game_over && ((millis() - time_update) > 250)){
    bitmasher.IncrementProgress((long) 1);
  }
  
  if(bitmasher.GetPlayer().score > player_win_value){
    text("you won!", 10, 90);
    game_over = true;
  }
  
  if(bitmasher.GetProgress() == bitmasher.GetWinAmt()){
    text("game over!", 10, 90);
    game_over = true;
  }
}

public void touchStarted(){
  
  if(game_over){
    NewGame();
    return;
  }
  
  boolean success = bitmasher.IslandSelected(mouseX, mouseY);
  if(!success){return;}
  
  Set<Cell> selection = bitmasher.GetIsland(
    bitmasher.GetXCellIndex(mouseX),
    bitmasher.GetYCellIndex(mouseY)
  );
  
  int x_min = bitmasher.GetLeftIslandBound(selection);
  int x_max = bitmasher.GetRightIslandBound(selection);
  println("x bounds: " + x_min + " | " + x_max);
  
  for(int i = x_min; i < (x_max + 1); i++){
    int y_min = bitmasher.GetX_YMinBound(i, selection);
    int y_max = bitmasher.GetX_YMaxBound(i, selection);
    println("y bounds at " + i + ": " + y_min + " | " + y_max);
    
    int y_diff = (y_max - y_min) + 1;
    for(int j = y_max; j > -1; j--){
      if((j - y_diff) > -1){
        bitmasher.GetBoard().SetCell(
          i, j, bitmasher.GetBoard().GetCell(i, j - y_diff)
        );
        bitmasher.GetBoard().GetCell(i, j).setPos(new PVector(i, j));
      } else {
        bitmasher.GetBoard().SetCell(
          i, j, new Cell(i, j)
        );
      }
    }
  }
  
  if(helped){
    bitmasher.DecrementProgress((long) 2 * selection.size());
    bitmasher.GetPlayer().score += (long) (2 * selection.size());
    helped = false;
  } else {
    bitmasher.DecrementProgress((long) 5 * selection.size());
    bitmasher.GetPlayer().score += (long) (5 * selection.size());
  }
  
  last_success_time = millis();
  bitmasher.FindIslands();
  
  if(bitmasher.GetIslands().size() == 0){
    bitmasher.MakeIsland();
    bitmasher.FindIslands();
  }
}
