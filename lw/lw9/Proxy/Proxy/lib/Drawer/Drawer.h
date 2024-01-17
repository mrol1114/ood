#pragma once

#include "../Image/Image.h"

/**
 * ������ ������� ������ ����� ����� ������� from � to ������ color �� ����������� Image.
 *
 * ��� ��������� ������������ �������� ����������.
 * (https://ru.wikipedia.org/wiki/��������_����������)
 */
void DrawLine(Image& image, Point from, Point to, char color);

void DrawCircle(Image& image, Point center, unsigned int radius, char color);

void DrawFilledCircle(Image& image, Point center, unsigned int radius, char color);