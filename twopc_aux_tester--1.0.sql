/* contrib/2pc_aux_tester/2pc_aux_tester--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION 2pc_aux_tester" to load this file. \quit

-- Extension comment
COMMENT ON EXTENSION 2pc_aux_tester 
IS 'Example extension with XactCallback for testing two-phase commit';

