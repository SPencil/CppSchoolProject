-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler version: 1.0.2
-- PostgreSQL version: 15.0
-- Project Site: pgmodeler.io
-- Model Author: ---
-- -- object: pg_database_owner | type: ROLE --
-- -- DROP ROLE IF EXISTS pg_database_owner;
-- CREATE ROLE pg_database_owner WITH 
-- 	INHERIT
-- 	 PASSWORD '********';
-- -- ddl-end --
-- 
-- object: urist | type: ROLE --
-- DROP ROLE IF EXISTS urist;
CREATE ROLE urist WITH 
	SUPERUSER
	CREATEDB
	CREATEROLE
	INHERIT
	LOGIN
	 PASSWORD '********';
-- ddl-end --

-- object: potatoe | type: ROLE --
-- DROP ROLE IF EXISTS potatoe;
CREATE ROLE potatoe WITH 
	INHERIT
	LOGIN
	 PASSWORD '********';
-- ddl-end --


-- Database creation must be performed outside a multi lined SQL file. 
-- These commands were put in this file only as a convenience.
-- 
-- object: "potatoesDB" | type: DATABASE --
-- DROP DATABASE IF EXISTS "potatoesDB";
CREATE DATABASE "potatoesDB"
	ENCODING = 'UTF8'
	LC_COLLATE = 'en_CA.utf8'
	LC_CTYPE = 'en_CA.utf8'
	TABLESPACE = pg_default
	OWNER = urist;
-- ddl-end --


-- object: public.tatertable_id_seq | type: SEQUENCE --
-- DROP SEQUENCE IF EXISTS public.tatertable_id_seq CASCADE;
CREATE SEQUENCE public.tatertable_id_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START WITH 1
	CACHE 1
	NO CYCLE
	OWNED BY NONE;

-- ddl-end --
ALTER SEQUENCE public.tatertable_id_seq OWNER TO urist;
-- ddl-end --

-- object: public.uom_table | type: TABLE --
-- DROP TABLE IF EXISTS public.uom_table CASCADE;
CREATE TABLE public.uom_table (
	uom text NOT NULL,
	uomid integer NOT NULL,
	CONSTRAINT uom_pkey PRIMARY KEY (uomid)
);
-- ddl-end --
ALTER TABLE public.uom_table OWNER TO urist;
-- ddl-end --

-- object: public.tatertable | type: TABLE --
-- DROP TABLE IF EXISTS public.tatertable CASCADE;
CREATE TABLE public.tatertable (
	uomid integer NOT NULL,
	scalarid integer NOT NULL,
	dguid integer NOT NULL,
	wasmodified integer NOT NULL,
	refdate integer NOT NULL,
	vector text NOT NULL,
	coordinate real NOT NULL,
	areaproductionvalue text NOT NULL,
	value numeric,
	status text,
	symbol text,
	terminated text,
	decimals integer NOT NULL,
	CONSTRAINT tatertable_pk PRIMARY KEY (refdate,vector,coordinate)
);
-- ddl-end --
ALTER TABLE public.tatertable OWNER TO urist;
-- ddl-end --

-- object: public.scalar_table | type: TABLE --
-- DROP TABLE IF EXISTS public.scalar_table CASCADE;
CREATE TABLE public.scalar_table (
	scalarfactor text NOT NULL,
	scalarid integer NOT NULL,
	CONSTRAINT scalar_pk PRIMARY KEY (scalarid)
);
-- ddl-end --
ALTER TABLE public.scalar_table OWNER TO urist;
-- ddl-end --

-- object: public.geo_table | type: TABLE --
-- DROP TABLE IF EXISTS public.geo_table CASCADE;
CREATE TABLE public.geo_table (
	geo text NOT NULL,
	dguid integer NOT NULL,
	CONSTRAINT geo_pk PRIMARY KEY (dguid)
);
-- ddl-end --
ALTER TABLE public.geo_table OWNER TO urist;
-- ddl-end --

-- object: public.wasmodified_table | type: TABLE --
-- DROP TABLE IF EXISTS public.wasmodified_table CASCADE;
CREATE TABLE public.wasmodified_table (
	wasmodified bool NOT NULL,
	modifiedid integer NOT NULL,
	CONSTRAINT modified_pk PRIMARY KEY (modifiedid)
);
-- ddl-end --
ALTER TABLE public.wasmodified_table OWNER TO urist;
-- ddl-end --

-- object: uom_fk | type: CONSTRAINT --
-- ALTER TABLE public.tatertable DROP CONSTRAINT IF EXISTS uom_fk CASCADE;
ALTER TABLE public.tatertable ADD CONSTRAINT uom_fk FOREIGN KEY (uomid)
REFERENCES public.uom_table (uomid) MATCH SIMPLE
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: scalar_fk | type: CONSTRAINT --
-- ALTER TABLE public.tatertable DROP CONSTRAINT IF EXISTS scalar_fk CASCADE;
ALTER TABLE public.tatertable ADD CONSTRAINT scalar_fk FOREIGN KEY (scalarid)
REFERENCES public.scalar_table (scalarid) MATCH SIMPLE
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: geo_fk | type: CONSTRAINT --
-- ALTER TABLE public.tatertable DROP CONSTRAINT IF EXISTS geo_fk CASCADE;
ALTER TABLE public.tatertable ADD CONSTRAINT geo_fk FOREIGN KEY (dguid)
REFERENCES public.geo_table (dguid) MATCH SIMPLE
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: modified_fk | type: CONSTRAINT --
-- ALTER TABLE public.tatertable DROP CONSTRAINT IF EXISTS modified_fk CASCADE;
ALTER TABLE public.tatertable ADD CONSTRAINT modified_fk FOREIGN KEY (wasmodified)
REFERENCES public.wasmodified_table (modifiedid) MATCH SIMPLE
ON DELETE NO ACTION ON UPDATE NO ACTION;
-- ddl-end --

-- object: "grant_CU_26541e8cda" | type: PERMISSION --
GRANT CREATE,USAGE
   ON SCHEMA public
   TO pg_database_owner;
-- ddl-end --

-- object: "grant_U_cd8e46e7b6" | type: PERMISSION --
GRANT USAGE
   ON SCHEMA public
   TO PUBLIC;
-- ddl-end --


