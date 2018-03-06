#ifndef HUD_H
#define HUD_H

class HUD {
private:
    int& _value;
public:
    HUD(int& value) : _value(value) { }
    void draw() const;
};

#endif // HUD_H


