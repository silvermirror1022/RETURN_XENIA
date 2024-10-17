// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define D(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, x); }
/*
*	<Debug용 스크립트>
*	사용할 CPP파일에 RXDebugHelper.h 추가한 후
*	디버그하고 싶은 변수 값을 다음과 같이 사용 가능 :
* 
*	해당 스코프에 CurrentHealth, MaxHealth 변수가 접근 가능한 경우,
*	D(FString::Printf(TEXT("Current Health: %f, Max Health: %f"), CurrentHealth, MaxHealth));
*/