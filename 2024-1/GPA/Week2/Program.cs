class Program {
  // 미리 선언된 Gun 목록
  private static readonly Gun[] PREDEFINED_GUNS = {
      new Gun("Machine Gun", 100000, "machine_gun", 2000),
      new Gun("Shotgun", 20000, "shot_gun", 100),
      new Gun("Mini Gun", 5000, "mini_gun", 500)
  };

  public static void Main(string[] args) {
    // 게임 시스템 생성
    GameSystem game = new();

    // 게임 프레임 업데이트 시 실행할 동작 추가
    game.OnUpdate += () => {
      game.Player.HP -= 1;
      game.Player.Stamina -= 2;

      PREDEFINED_GUNS[0].AmmoAmount -= 10;
      PREDEFINED_GUNS[1].Upgrade(1);
      PREDEFINED_GUNS[2].Upgrade(20);
    };

    // 미리 선언된 Gun들을 인벤토리에 추가
    foreach(var gun in PREDEFINED_GUNS) {
      game.Player.Inventory.Put(gun);
    }

    // 게임 시작
    game.Start();
  }
}

/* 게임 시스템 클래스 */
class GameSystem {
  public enum GameStatus {
    // 게임 상태

    Initialize,
    Start,
    Update,
    Stop,
    End,
    Error
  }

  // 프레임 업데이트 간격
  private const int UPDATE_TIME = 500;

  // 최대 프레임 수
  private const int MAX_FRAME_COUNT = 100;

  // 업데이트 스레드
  private Thread updateThread;

  // 게임 중지 요청 플래그
  private bool requestStopFlag = false;

  public GameSystem() {
    // 게임 시스템 생성 시 업데이트 스레드에 함수 지정
    updateThread = new Thread(Update);
  }

  // 플레이어
  public Player Player { get; } = new();

  // 게임 상태
  public GameStatus Status { get; private set; } = GameStatus.Initialize;

  // 현재 프레임 수
  public int CurrentFrameCount { get; private set; } = -1;

  // 매 프레임 업데이트 시 실행되는 delegate
  public Action OnUpdate { get; set; }

  // 게임 중단 시 실행되는 delegate
  public Action OnStop { get; set; }

  public void Start() {
    // 게임 시작 시 게임 상태 변경 및 업데이트 스레드 시작

    Status = GameStatus.Start;

    updateThread.Start();
  }

  public void RequestStop() {
    // 게임 중단 요청

    if(Status != GameStatus.Update)
      return;

    requestStopFlag = true;
  }

  private void Update() {
    // 게임 프레임 업데이트

    while(true) {
      // 상태 설정
      Status = GameStatus.Update;

      // 프레임 수 증가
      CurrentFrameCount++;

      // 게임 중단이 요청된 경우 or 플레이어 체력이 0으로 떨어진 경우
      // or 현재 프레임이 최대 프레임 수를 초과한 경우
      // 게임 중단
      if(requestStopFlag || Player.HP <= 0 || CurrentFrameCount >= MAX_FRAME_COUNT) {
        Status = GameStatus.Stop;
        Stop();
        return;
      }

      try {
        // 프레임 업데이트 delegate 실행
        OnUpdate?.Invoke();

        // 프레임 업데이트 간격만큼 대기
        Thread.Sleep(UPDATE_TIME);

        // 콘솔 화면에 게임 내용 출력
        Render();
      } catch {
        // 오류 발생 시 게임 중단

        Status = GameStatus.Error;
        Stop(error: true);
        return;
      }
    }
  }

  private void Render() {
    Console.WriteLine("===== FRAME UPDATE =====");
    Console.WriteLine("== Game Statistics ==");
    Console.WriteLine($"* Game status: {Status.ToString()}");
    Console.WriteLine($"* Frame count: {CurrentFrameCount}");
    Console.WriteLine();

    Console.WriteLine("== Player Statistics ==");
    Console.WriteLine($"* HP: {Player.HP} / {Player.MAX_HP}");
    Console.WriteLine($"* Stamina: {Player.Stamina} / {Player.MAX_STAMINA}");
    Console.WriteLine();

    Console.WriteLine("== Inventory Statistics ==");
    Console.WriteLine($"* Inventory count: {Player.Inventory.Count()}");
    using var enumerator = Player.Inventory.GetEnumerator();
    while(enumerator.MoveNext()) {
      // 플레이어 인벤토리 내 아이템을 순회하면서 내용 출력
      enumerator.Current.Describe();
    }

    Console.WriteLine();
  }

  private void Stop(bool error = false) {
    Status = GameStatus.End;

    OnStop?.Invoke();

    Console.WriteLine(error ? "===== GAME EXIT (with error(s)) =====" : "===== GAME END =====");
  }
}

class Player {
  public const int MAX_HP = 100;
  public const int MAX_STAMINA = 200;

  private int _hp = 100;
  private int _stamina = 200;

  public int HP {
    get { return _hp; }
    set {
      if(value < 0)
        value = 0;
      _hp = value;
    }
  }
  public int Stamina {
    get { return _stamina; }
    set {
      if(value < 0)
        value = 0;
      _stamina = value;
    }
  }

  public Inventory Inventory { get; } = new();
}

class Inventory {
  private List<Item> items = new();

  ~Inventory() {
    items.RemoveAll(_ => true);
  }

  public void Put(Item item) {
    items.Add(item);
  }

  public void Remove(Item item) {
    items.Remove(item);
  }

  public void Remove(int index) {
    items.RemoveAt(index);
  }

  public void Remove(Guid id) {
    items.RemoveAll(item => item.id == id);
  }

  public Item? Get(int index) {
    try {
      return items[index];
    } catch {
      return null;
    }
  }

  public Item? Get(Guid id) {
    return items.Find(item => item.id == id);
  }

  public int Count() {
    return items.Count;
  }

  public List<Item>.Enumerator GetEnumerator() {
    return items.GetEnumerator();
  }
}

class Item {
  public readonly Guid id = Guid.NewGuid();
  public string name;
  public string shape;

  public Item(string name, string shape) {
    this.name = name;
    this.shape = shape;
  }

  public virtual void Describe() {
    Console.WriteLine($"-- Item (ID {id})");
    Console.WriteLine($" Name: {name}");
    Console.WriteLine($" Shape: {shape}");
  }
}

class Weapon: Item {
  private int _damage;
  public int Damage {
    get { return _damage; }
    set {
      if(value < 0)
        value = 0;
      _damage = value;
    }
  }

  public Weapon(string name, int damage, string shape) : base(name, shape) {
    Damage = damage;
  }

  public void Upgrade(int amount = 10) {
    Damage += amount;
  }

  public override void Describe() {
    base.Describe();
    Console.WriteLine($" Damage: {Damage}");
  }
}

class Gun: Weapon {
  private int _ammoAmount;
  public int AmmoAmount {
    get { return _ammoAmount; }
    set {
      if(value < 0)
        value = 0;
      _ammoAmount = value;
    }
  }

  public Gun(string name, int damage, string shape, int ammoAmount) : base(name, damage, shape) {
    AmmoAmount = ammoAmount;
  }

  public override void Describe() {
    base.Describe();
    Console.WriteLine($" Ammo: {AmmoAmount}");
  }
}
