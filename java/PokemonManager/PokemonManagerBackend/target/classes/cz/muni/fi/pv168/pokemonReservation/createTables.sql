
CREATE TABLE "CUSTOMER" (
    "ID" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    "NAME" VARCHAR(63) NOT NULL
);

CREATE TABLE "POKEMON" (
    "ID" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    "NAME" VARCHAR(63) NOT NULL,
    "POWER" INT NOT NULL,
    "HEALTH" INT NOT NULL
);

CREATE TABLE "RESERVATION" (
    "ID" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    "FROMDATE" TIMESTAMP NOT NULL,
    "TODATE" TIMESTAMP NOT NULL,
    "POKEMONID" INT NOT NULL,
   "CUSTOMERID" INT NOT NULL,
   CONSTRAINT POKEMONFK FOREIGN KEY (POKEMONID) REFERENCES POKEMON (ID),
   CONSTRAINT CUSTOMERFK FOREIGN KEY (CUSTOMERID) REFERENCES CUSTOMER (ID)
);