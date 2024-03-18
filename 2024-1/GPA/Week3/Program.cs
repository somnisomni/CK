class Program {
    static void Main(string[] args) {
        // #1 프로퍼티
        Console.WriteLine("\n #1 프로퍼티");
        
        FPSPlayer.Example();
        
        // #2-1 인덱서
        Console.WriteLine("\n #2-1 인덱서");
        
        var tempRecord = new TempRecord();
        tempRecord[3] = 58.3F;
        tempRecord[5] = 60.1F;
        for(var i = 0; i < 10; i++) {
            Console.WriteLine($"Element #{i} = {tempRecord[i]}");
        }
        
        // #2-2 인덱서
        Console.WriteLine("\n #2-2 인덱서");
        
        var data = new TCGCardDataCollection();
        Console.WriteLine(data[TCGCardDataCollection.CardKind.ACE]);
        
        // #3 리스트
        Console.WriteLine("\n #3 리스트");
        
        var list = new List<string>();
        
        Console.WriteLine("이름 5개 입력");
        foreach(var _ in Enumerable.Range(0, 5)) {
            Console.Write(" > ");
            list.Add(Console.ReadLine()!);
        }
        
        Console.WriteLine("정렬 및 출력");
        list.Sort((s1, s2) => s1.Length - s2.Length);
        list.ForEach(Console.WriteLine);
        
        // #4 스택
        Console.WriteLine("\n #4 스택");
        
        var stack = new Stack<string>();
        stack.Push("Korea");
        stack.Push("USA");
        stack.Push("Canada");
        stack.Push("France");
        stack.Push("England");
        while(stack.Count > 0) {
            Console.WriteLine("Stack peek: {0}", stack.Peek());
            stack.Pop();
        }
        
        // #5 큐
        Console.WriteLine("\n #5 큐");
        
        var queue = new Queue<int>();
        queue.Enqueue(20);
        queue.Enqueue(30);
        queue.Enqueue(10);
        queue.Dequeue();
        queue.Enqueue(70);
        queue.Enqueue(35);
        queue.Dequeue();
        while(queue.Count > 0) {
            Console.WriteLine("Queue peek: {0}", queue.Peek());
            queue.Dequeue();
        }
        
        // #6 딕셔너리
        Console.WriteLine("\n #6 딕셔너리");

        var dict = new Dictionary<string, List<string>>();
        var firstInput = Console.ReadLine()!.Split();  // 첫 줄 입력 (선수 수, 대상 구단)
        var count = int.Parse(firstInput[0]);  // 선수 수
        var targetTeamName = firstInput[1]; // 대상 구단
        
        // 선수 수 만큼 선수 정보 입력 받기
        foreach(var _ in Enumerable.Range(0, count)) {
            var input = Console.ReadLine()!.Split();
            
            // 딕셔너리에 구단에 따른 선수 추가
            if(dict.TryGetValue(input[0], out var value)) {
                value.Add(input[1]);
            } else {
                dict[input[0]] = new List<string> { input[1] };
            }
        }
        
        // 대상 구단 내의 선수 출력
        Console.WriteLine("\n대상 구단: {0}", targetTeamName);
        if(dict.TryGetValue(targetTeamName, out var result)) {
            result.Sort();
            result.ForEach(Console.WriteLine);
        } else {
            Console.WriteLine("(선수 없음)");
        }
    }
}
