#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
using namespace std;

vector<vector<vector<double>>> CreatVector(int width, int height, int action_count)
{
    vector<vector<vector<double>>> field;
    for (int x = 0; x < width; x++)
    {
        vector<vector<double>> fieldy;
        for (int y = 0; y < height; y++)
        {
            vector<double> fielda;
            for (int a = 0; a < action_count; a++)
            {
                fielda.push_back(0);
            }
            fieldy.push_back(fielda);
        }
        field.push_back(fieldy);
    }
    return field;
}
vector<vector<double>> CreatVector(int width, int height, double value = 0)
{
    vector<vector<double>> field;
    for (int x = 0; x < width; x++)
    {
        vector<double> fieldy;
        for (int y = 0; y < height; y++)
        {
            fieldy.push_back(value);
        }
        field.push_back(fieldy);
    }
    return field;
}

//Функция для получения случайного натурального числа от min до max
int GetRandomNumber(int min, int max)
{
    int num = min + rand() % (max - min + 1);
    return num;
}

ostream& operator<< (ostream& stream, vector<double> v)
{
    stream << "\nVector:\n( ";
    for (int i = 0; i < v.size() - 1; i++) {
        stream << v[i] << ", ";
    }
    stream << v[v.size() - 1];
    stream << " )\n";


    return stream;
}
ostream& operator<< (ostream& stream, vector<vector<double>> v)
{
    stream << "\nVector:\n";
    for (int y = 0; y < v[0].size(); y++) {
        for (int x = 0; x < v.size(); x++) {
            stream << v[x][y] << "\t";
        }
        stream << "\n";
    }
    return stream;
}
ostream& operator<< (ostream& stream, vector<vector<vector<double>>> v)
{
    stream << "\nVector:\n";
    for (int a = 0; a < v[0][0].size(); a++) {
        if (a == 0) { cout << "Right:\n"; }
        else if (a == 1) { cout << "Left:\n"; }
        else if (a == 2) { cout << "Down:\n"; }
        else if (a == 3) { cout << "Up:\n"; }

        for (int y = 0; y < v[0].size(); y++) {
            for (int x = 0; x < v.size(); x++) {
                stream << v[x][y][a] << "\t";
            }
            stream << "\n";
        }
        stream << "------------\n";
    }
    return stream;
}



//Дискретное поле
class Field {
protected:
    int width;
    int height;
   
    vector<vector<double>> mas;
    vector<vector<double>> getField() const { return mas; }

    // Награда за клетку:    ||| Вероятность, что следующая клетка будет указанного цвета  
    // -1 - белая клетка (б)   -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // -2 - синяя клетка (с)   -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // -3 - красная клетка (к) -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // -4 - желтая клетка (ж)  -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // -5 - зеленая клетка (з) -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // -15 - черная клетка (ч) -  б: 0.25, c: 0.1, к: 0.3, ж: 0.25, з: 0.05, ч: 0.05
    // 25 - выход
    vector<vector<double>> propabilities = {{ 0.25, 0.1, 0.3, 0.25, 0.05, 0.05 },
                                            { 0.2, 0.15, 0.2, 0.3, 0.05, 0.1 },
                                            { 0.1, 0.1, 0.1, 0.55, 0.05, 0.1 },
                                            { 0.25, 0.1, 0.3, 0.25, 0.05, 0.05 },
                                            { 0.25, 0.15, 0.25, 0.15, 0.1, 0.1 },
                                            { 0.15, 0.1, 0.4, 0.15, 0.1, 0.1 }};
    
    vector<int> rewards = { -1, -2, -3, -4, -5, -15 };
    int max_reward = 25;

public:
    Field() { width = 0; height = 0; }
    Field(int w, int h) { width = w; height = h; mas = CreatVector(w, h); }
    Field(int w, int h, double value) { width = w; height = h; mas = CreatVector(w, h, value); }
    Field(vector<vector<double>> f, int w, int h) { mas = f; width = w; height = h; }
    Field(const Field& f) { width = f.getWidth(); height = f.getHeight(); mas = f.getField(); }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getFieldElement(int x, int y) const { return mas[x][y]; }

    void setValue(int x, int y, double value) {
        if (x >= width or x < 0 or y >= height or y < 0) { throw "Value isn't correct"; }
        mas[x][y] = value;
    }

    int getReward(int this_reward) {
        double pr = GetRandomNumber(0, 99)*0.01;
        int action = 0;
        for (int i = 0; i < rewards.size(); i++) {
            if (this_reward == rewards[i]) { action = i; }
        }
        double sumpr = 0;
        for (int i = 0; i < propabilities.size(); i++) {
            sumpr += propabilities[action][i];
            if (sumpr >= pr) {
                return rewards[i];
            }
        }
    }
    void setNextReward(vector<int> thispos, vector<int> nextpos) {
        if (nextpos[0] == width - 1 and
            nextpos[1] == height - 1)
        {
            mas[nextpos[0]][nextpos[1]] = max_reward;
        }
        else {
            mas[nextpos[0]][nextpos[1]] = getReward(mas[thispos[0]][thispos[1]]);
        }
    }

    Field& operator= (const Field& other) {
        width = other.getWidth(); height = other.getHeight();
        this->mas = other.getField(); return *this; }

    friend ostream& operator<< (ostream& stream, const Field& f);
};

ostream& operator<< (ostream& stream, const Field& f)
{
    stream << "\nField:\n";
    for (int y = 0; y < f.height; y++) {
        for (int x = 0; x < f.width; x++) {
            stream << f.mas[x][y] << "\t";
        }
        stream << "\n";
    }
    return stream;
}


//Агент, исследующий поле
class Agent {
protected:
    int start_pos_x;
    int start_pos_y;

    int pred_pos_x;
    int pred_pos_y;

    int pos_x;
    int pos_y;
public:
    Agent() { start_pos_x = start_pos_y = 
              pos_x = pos_y =
              pred_pos_x = pred_pos_y = 0; }
    Agent(int x, int y) { 
        if (x < 0 or y < 0)
            throw "Coordinates of the agent aren't correct!";
        start_pos_x = pos_x = pred_pos_x = x; start_pos_y = pos_y = pred_pos_y = y; }
    Agent(const Agent& a) {
        start_pos_x = a.getStartPosition()[0]; start_pos_y = a.getStartPosition()[1];
        pos_x = a.getPosition()[0]; pos_y = a.getPosition()[1];
        pred_pos_x = a.getPredPosition()[0]; pred_pos_y = a.getPredPosition()[1];
    }
    ~Agent() {}

    vector<int> getPosition() const { vector<int> res = { pos_x, pos_y}; return res; }
    void setPosition(vector<int> pos) { pos_x = pos[0]; pos_y = pos[1]; }
    void setPosition(int x, int y) { pos_x = x; pos_y = y; }

    vector<int> getPredPosition() const { vector<int> res = { pred_pos_x, pred_pos_y }; return res; }
    void setPredPosition(vector<int> predpos) { pred_pos_x = predpos[0]; pred_pos_y = predpos[1]; }
    void setPredPosition(int x, int y) { this->pred_pos_x = x; this->pred_pos_y = y; }

    vector<int> getStartPosition() const { vector<int> res = { start_pos_x , start_pos_y }; return res; }
    void RestartPosition() { pos_x = pred_pos_x = start_pos_x; pos_y = pred_pos_y = start_pos_y; }
    int getx() { return pos_x; }
    int gety() { return pos_y; }

    int getpredx() { return pred_pos_x; }
    int getpredy() { return pred_pos_y; }

    vector<int> RandomStep()
    {
        //выбираем, по какой оси будем делать шаг
        int xory = GetRandomNumber(0, 1); //0 - x, 1 - y
        //размер шага
        int step = GetRandomNumber(0, 1); //шаг -1 либо 1
        if (step == 0) { step = -1; }

        vector<int> result;
        if (xory)
        {
            result.push_back(pos_x);
            result.push_back(pos_y + step);
        }
        else {
            result.push_back(pos_x + step);
            result.push_back(pos_y);

        }
        return result;
    }

    Agent& operator= (const Agent& a) {
        this->start_pos_x = a.getStartPosition()[0]; this->start_pos_y = a.getStartPosition()[1];
        this->pos_x = a.getPosition()[0]; this->pos_y = a.getPosition()[1];
        this->pred_pos_x = a.getPredPosition()[0]; this->pred_pos_y = a.getPredPosition()[1];
        return *this; }
};

class Game {
protected:
    Agent agent;
    Field field;

    int t = 0; // общее кол-во шагов
    double Rt = 0; //общее полученное вознаграждение к текущему моменту
    int view_t = 0; //кол-во шагов в текущей итерации
    double view_Rt = 0; //набранное вознаграждение в текущей итерации
    vector<double> result_Rt;
    vector<double> result_t;

    int width = 0;
    int height = 0;
    vector<vector<vector<double>>> Nt_a; // сколько раз действие a выбиралось до момента t (для UCB)
    vector<vector<vector<double>>> Qt_a; //ожидаемое вознаграждение (также V(St)) при действии a
    vector<vector<double>> Nt;  // кол-во шагов в текущую клетку

protected:
    int Action(vector<int> pos, vector<int> pred_pos) {
        int action = 0;
        if (pos[0] - pred_pos[0] == -1) {
            action = 1;
        }
        else if (pos[1] - pred_pos[1] == 1) {
            action = 2;
        }
        else if (pos[1] - pred_pos[1] == -1) {
            action = 3;
        }
        return action;
    }
    vector<int> Action(vector<int> pos, int act) {
        vector<int> res = pos;
        if (act == 0) {
            res[0] += 1;
        }
        else if (act == 1) {
            res[0] -= 1;
        }
        else if (act == 2) {
            res[1] += 1;
        }
        else if (act == 3) {
            res[1] -= 1;
        }
        return res;
    }
    bool BorderPosition() {
        int x = agent.getx();
        int y = agent.gety();
        if (x >= 0 and x < field.getWidth() and
            y >= 0 and y < field.getHeight())
        {
            return 1;
        }
        return 0;
    }
    bool BorderPosition(int x, int y) {
        if (x >= 0 and x < field.getWidth() and y >= 0 and y < field.getHeight())
        {
            return 1;
        }
        return 0;
    }
    //Эпсилон жадная стратегия
    bool Epsilon(double epsilon) {
        double probability = GetRandomNumber(1, 999) * 0.001;
        if (probability < epsilon) { return 1; }
        return 0;
    }

    void Clear() { view_t = 0; view_Rt = 0; }
    //============================================================
    //Обучение через метод UCB
    vector<int> UCBLearning(int iteration) {
        if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
        {
            cout << *this << "\n===============\n";
        }
        while (1) {
            if (Epsilon(epsilon_ucb)) { RandomStepUpdateUCB(iteration); }
            else { UCB(iteration); }

            if (agent.getx() == (field.getWidth() - 1) and agent.gety() == (field.getHeight() - 1))
            {
                agent.RestartPosition();
                vector<int> res;
                res.push_back(view_t);
                res.push_back(view_Rt);
                result_t.push_back(view_t);
                result_Rt.push_back(view_Rt);

                Clear();
                return res;
            }
        }
    }
    void UCB(int iteration) {
        int x = agent.getx();
        int y = agent.gety();
        vector<int> oldpos = agent.getPosition();

        int action = argmaxUCB(x, y);
        vector<int> newpos = Action(agent.getPosition(), action);

        // Задаем случайный цвет, в этом случае поле нестатично
        if (propabilities_color) {
            field.setNextReward(oldpos, newpos);
        }

        
        UpdateUCB(action);
        Nt_a[x][y][action] += 1;
        Nt[newpos[0]][newpos[1]] += 1;
        agent.setPredPosition(x, y);
        agent.setPosition(newpos[0], newpos[1]);
        
        if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
        {
            cout << *this << "\n===============\n";
        }
    }

    void RandomStepUpdateUCB(int iteration) {
        vector<int> newpos = agent.RandomStep();

        if (BorderPosition(newpos[0], newpos[1])) {
            vector<int> pos = agent.getPosition();
            int action = Action(newpos, pos);

            // Задаем случайный цвет, в этом случае поле нестатично
            if (propabilities_color) {
                field.setNextReward(pos, newpos);
            }

            UpdateUCB(action);
            Nt_a[pos[0]][pos[1]][action] += 1;
            Nt[newpos[0]][newpos[1]] += 1;
            agent.setPredPosition(pos[0], pos[1]);
            agent.setPosition(newpos[0], newpos[1]);
            

            if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
            {
                cout << *this << "\n===============\n";
            }
        }
        else
            RandomStepUpdateUCB(iteration);
    }
    int argmaxUCB(int x, int y) {
        vector<int> pos = { x, y };
        vector<int> actions;

        if (BorderPosition(x + 1, y)) {
            actions.push_back(0);
        }
        if (BorderPosition(x - 1, y)) {
            actions.push_back(1);
        }
        if (BorderPosition(x, y + 1)) {
            actions.push_back(2);
        }
        if (BorderPosition(x, y - 1)) {
            actions.push_back(3);
        }

        double value1; double value2;
        int act_max = actions[GetRandomNumber(0, actions.size() - 1)];
        for (int i = 0; i < actions.size(); i++) {

            value1 = Qt_a[x][y][actions[i]] + c * sqrt(log(t) / Nt_a[x][y][actions[i]]);
            value2 = Qt_a[x][y][act_max] + c * sqrt(log(t) / Nt_a[x][y][act_max]);
            if (value1 > value2)
                act_max = actions[i];
        }

        vector<int> max_actions;
        max_actions.push_back(act_max);

        value2 = Qt_a[x][y][act_max] + c * sqrt(log(t) / Nt_a[x][y][act_max]);
        for (int i = 0; i < actions.size(); i++) {
            vector<int> nextpos = Action(pos, actions[i]);

            value1 = Qt_a[x][y][actions[i]] + c * sqrt(log(t) / Nt_a[x][y][actions[i]]);
            if (value1 == value2 or Nt[nextpos[0]][nextpos[1]] == 0)
                max_actions.push_back(actions[i]);
        }

        act_max = max_actions[GetRandomNumber(0, max_actions.size() - 1)];
        return act_max;
    }

    void UpdateUCB(int action) {
        int x = agent.getx();
        int y = agent.gety();

        t += 1;
        Rt += field.getFieldElement(x, y);
        view_t += 1;
        view_Rt += field.getFieldElement(x, y);

        double Qt_new = view_Rt / Nt[x][y]; //Nt_a[x][y][action];
        Qt_a[x][y][action] = Qt_new;
    }
    //============================================================

    //============================================================
    //TD - обучение
    vector<int> TDLearning(int iteration) {
        if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
        {
            cout << *this << "\n===============\n";
        }
        while (1) {
            if (Epsilon(epsilon_td)) { RandomStepUpdateTD(iteration); }
            else { TD(iteration); }

            if (agent.getx() == (field.getWidth() - 1) and agent.gety() == (field.getHeight() - 1)) {
                agent.RestartPosition();
                vector<int> res;
                res.push_back(view_t);
                res.push_back(view_Rt);
                result_t.push_back(view_t);
                result_Rt.push_back(view_Rt);

                Clear();
                return res;
            }
        }
    }
    void TD(int iteration) {
        int x = agent.getx();
        int y = agent.gety();
        vector<int> pos = agent.getPosition();

        int action = argmaxTD(x, y);
        vector<int> newpos = Action(pos, action);
        // Задаем случайный цвет, в этом случае поле нестатично
        if (propabilities_color) {
            field.setNextReward(pos, newpos);
        }

        agent.setPredPosition(x, y);
        agent.setPosition(newpos[0], newpos[1]);

        UpdateTD(action);
        
        if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
        {
            cout << *this << "\n===============\n";
        }
    }

    void RandomStepUpdateTD(int iteration) {
        vector<int> newpos = agent.RandomStep();

        if (BorderPosition(newpos[0], newpos[1])) {
            int action = Action(newpos, agent.getPosition());
            // Задаем случайный цвет, в этом случае поле нестатично
            vector<int> pos = agent.getPosition();
            if (propabilities_color) {
                field.setNextReward(pos, newpos);
            }

            agent.setPredPosition(agent.getx(), agent.gety());
            agent.setPosition(newpos[0], newpos[1]);
            UpdateTD(action);
            
            if (print_agent or (last_iteration and iteration == (iteration_count - 1)))
                { cout << *this << "\n===============\n"; }
        }
        else
            RandomStepUpdateTD(iteration);
    }

    int argmaxTD(int x, int y) {
        vector<int> pos = { x, y };
        vector<int> actions;

        if (BorderPosition(x + 1, y)) {
            actions.push_back(0);
        }
        if (BorderPosition(x - 1, y)) {
            actions.push_back(1);
        }
        if (BorderPosition(x, y + 1)) {
            actions.push_back(2);
        }
        if (BorderPosition(x, y - 1)) {
            actions.push_back(3);
        }
        
        int act_max = actions[GetRandomNumber(0, actions.size()-1)];
        for (int i = 0; i < actions.size(); i++) {
            if (Qt_a[x][y][actions[i]] > Qt_a[x][y][act_max])
                act_max = actions[i];
        }

        vector<int> max_actions;
        for (int i = 0; i < actions.size(); i++) {
            vector<int> nextpos = Action(pos, actions[i]);

            if (Qt_a[x][y][actions[i]] == Qt_a[x][y][act_max] or Nt[nextpos[0]][nextpos[1]] == 0)
                max_actions.push_back(actions[i]);
        }

        act_max = max_actions[GetRandomNumber(0, max_actions.size() - 1)];
        return act_max;
    }

    void UpdateTD(int action) {
        int x = agent.getx();
        int y = agent.gety();

        int predx = agent.getpredx();
        int predy = agent.getpredy();

        double R_next = field.getFieldElement(x, y);

        t += 1;
        view_t += 1;
        view_Rt += field.getFieldElement(x, y);
        Rt += view_Rt;

        double V_St_pred = Qt_a[predx][predy][action];
        double V_St_next = Qt_a[x][y][argmaxTD(x, y)];

        double V_St_new = V_St_pred + alpha * (R_next + gamma * V_St_next - V_St_pred);
        Qt_a[predx][predy][action] = V_St_new;

        Nt[x][y] += 1;
    }

    //============================================================

    friend ostream& operator<< (ostream& stream, Game& g);
public:
    //из TD
    double alpha = 0.9; //параметры обучения
    double gamma = 0.85;
    double epsilon_td = 0.05; //для TD обучения

    // Из UCB
    double c = 2.4; //константа из UCB
    double epsilon_ucb = 0.05; // параметр из эпсилон жадной стратегии (для UCB)

    // Общие настройки
    int iteration_count = 100; // сколько раз модель будет обучаться
    bool print_agent = 0; //вывод результата ходьбы агента на каждом шаге (0/1 соответственно)
    bool last_iteration = 0; //вывод ходов агента на последнем обучении

    // Определяет динамичность поля
    bool propabilities_color = true;

    Game() {}
    Game(Field f) { field = f; }
    Game(Agent a, int width0, int height0) {
        if (width0 <= 1 and height0 <= 1) { throw "The size of field is very little"; }
        agent = a; Field newf(width0, height0); field = newf;
        width = width0; height = height0;
        propabilities_color = true;
    }
    Game(Field f, Agent a) {
        if ((a.getPosition())[0] >= f.getWidth() or (a.getPosition())[0] < 0 or
            (a.getPosition())[1] >= f.getHeight() or (a.getPosition())[1] < 0)
        {
            throw "Coordinates of the agent aren't correct!";
        }
        field = f;
        agent = a;
        propabilities_color = false;

        width = f.getWidth();
        height = f.getHeight();
    }
    Game(const Game& g) { agent = g.getAgent(); field = g.getField(); }

    Agent getAgent() const { return agent; }
    Field getField() const { return field; }

    vector<double> get_Rt() { return result_Rt; }
    vector<double> get_t() { return result_t; }
    int getTotal_t() { return t; }
    int getTotal_r() { return Rt; }

    int getIterCount() { return iteration_count; }

    void ClearGame() {
        t = 0; Rt = 0;
        Qt_a = CreatVector(field.getWidth(), field.getHeight(), 4);
        Nt = CreatVector(field.getWidth(), field.getHeight());
        Nt_a = CreatVector(field.getWidth(), field.getHeight(), 4);
        result_Rt.clear(); result_t.clear();
    }
    void MethodUCB() {
        Qt_a = CreatVector(width, height, 4); //right, left, down, up
        Nt_a = CreatVector(width, height, 4);
        Nt = CreatVector(width, height);

        for (int i = 0; i < iteration_count; i++) {
            vector<int> getres = UCBLearning(i);
        }
        cout << "\nUCB learning was successfull\n";
    }
    void MethodTD() {
        Qt_a = CreatVector(width, height, 4); //right, left, down, up
        Nt = CreatVector(width, height);

        for (int i = 0; i < iteration_count; i++) {
            vector<int> getres = TDLearning(i);
        }
        cout << "\nTD learning was successfull\n";
    }
    void print() {
        if (t == 0) { throw "You need do learning to see results"; }

        cout << "\n\nQt_a:\n" << Qt_a;
        cout << "\n\nNt:\n" << Nt;

        cout << "\nRewards:" << get_Rt();
        cout << "\nSteps:" << get_t();
    }

};
ostream& operator<< (ostream& stream, Game& g)
{
    stream << "\Game:\n";
    for (int y = 0; y < (g.field).getHeight(); y++) {
        for (int x = 0; x < (g.field).getWidth(); x++) {
            if (x == ((g.agent).getPosition())[0] and y == ((g.agent).getPosition())[1])
                stream << "*\t";
            else
                stream << (g.field).getFieldElement(x, y) << "\t";
        }
        stream << "\n";
    }
    return stream;
}

int main()
{
    try
    {
        // Для генератора случайных чисел
        srand(time(NULL));

        Agent a(0, 0);
        Game newgame(a, 4, 4);

        cout << newgame << "\n===================\n";


        newgame.c = 30;
        newgame.epsilon_ucb = 0.007;

        newgame.alpha = 0.4;
        newgame.gamma = 0.7;
        newgame.epsilon_td = 0.01;
        newgame.iteration_count = 500;
        newgame.last_iteration = true;
        //newgame.propabilities_color = false;

        //newgame.MethodUCB();
        //newgame.print();
        //newgame.ClearGame();
        newgame.MethodTD();
        newgame.print();

        string len;
        cin >> len;
        return 0;
    }
    catch (const char* error) { cout << error; }
}


