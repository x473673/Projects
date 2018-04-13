/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.threadapp;

import java.io.IOException;
import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author trnka
 */
public class ThreadDemo {
 
    private static long number = 0;
 
    private static Logger logger = Logger.getLogger(ThreadDemo.class.getName());
 
    private static class Counter implements Runnable {
 
        @Override
        public synchronized void run() {
            while (number <= 50) {
                System.out.println(Thread.currentThread().getName() + ": " + number++);
            }
        }
    }
    
    public static void main(String... args) throws IOException {
        for (int i = 0; i < 3; i++) {
            Thread thread = new Thread(new Counter(), "Vlakno " + i);
            thread.start();
        }
    }
}
